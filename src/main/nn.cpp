/**
 * TODO: Depericate (replace with rr_nn)
 * Code to control the neural network.
 */

// TODO: depreicate this
#include "nn.hpp"

//TODO: Remove these macros and replace with functions,  will need functions to process
// multiple hidden layers easily.
// Private Macros
#define _initialize_(_nodes_sz_, _input_nodes_sz_, _change_weights_, _weights_) \
  for (int i = 0; i < _nodes_sz_; i++)                                          \
  {                                                                             \
    for (int j = 0; j <= _input_nodes_sz_; j++)                                 \
    {                                                                           \
      _change_weights_[j][i] = 0.0;                                             \
      _weights_[j][i] = 2.0 * (RANDO - 0.5) * _initial_weight_max;              \
    }                                                                           \
  }

#define _setup_change_weights_(_x_, _y_, _s_)        \
  for (it = _x_.begin(); it != _x_.end(); it++, i++) \
  {                                                  \
    vector<float> f, y;                              \
    f.resize(_s_);                                   \
    y.resize(_s_);                                   \
    _x_.at(i) = f;                                   \
    _y_.at(i) = y;                                   \
  }

// based on https://codingnest.com/generating-random-numbers-using-c-standard-library-the-problems/
//
// In theory this code should use the /dev/urandom or any other hardware set as the random number generator.
// float nn_random()
// {
//   // Truly random seed.
//   std::mt19937 rng(std::random_device{}());

//   // Avoid constructing distribution all the time
//   std::uniform_int_distribution<> dist(0, 100);

//   float r = float(dist(rng)) / 100.0f;

//   return r;
// }


void NN::setup(string nid, ConfigReader config)
{
  _nid = nid;
  _initial_weight_max = config.nn_inital_weight(_nid);
  _input_nodes_sz = config.input_nodes(_nid);
  _hidden_nodes_sz = config.hidden_nodes(_nid);
  _output_nodes_sz = config.output_nodes(_nid);
  _success = config.nn_success(_nid);
  _learning_rate = config.nn_learning_rate(_nid);
  _momentum = config.nn_momentum(_nid);

  _hidden_weights.resize(_input_nodes_sz + 1);
  _change_hidden_weights.resize(_input_nodes_sz + 1);
  _hidden._delta.resize(_hidden_nodes_sz, 1);

  _output_weights.resize(_hidden_nodes_sz + 1);
  _change_output_weights.resize(_hidden_nodes_sz + 1);
  _output._delta.resize(_output_nodes_sz, 2);
  _output._nodes.resize(_output_nodes_sz, 0);

  int i = 0;
  vector<vector<float>>::iterator it;
  _setup_change_weights_(_change_hidden_weights, _hidden_weights, _hidden_nodes_sz);

  i = 0;
  _setup_change_weights_(_change_output_weights, _output_weights, _output_nodes_sz);

  _hidden._nodes.resize(_hidden_nodes_sz, 0.);
}

/******************************************************************
 * Initialize HiddenWeights and ChangeHiddenWeights
 ******************************************************************/
void NN::initialize_hidden()
{
  Logger::info("Initialize HiddenWeights and ChangeHiddenWeights");
  _initialize_(_hidden_nodes_sz, _input_nodes_sz, _change_hidden_weights, _hidden_weights);
}

/******************************************************************
 * Initialize OutputWeights and ChangeOutputWeights
 ******************************************************************/
void NN::initialize_output()
{
  Logger::info("Initialize OutputWeights and ChangeOutputWeights");
  _initialize_(_output_nodes_sz, _hidden_nodes_sz, _change_output_weights, _output_weights);
}

/******************************************************************
 * Begin training
 ******************************************************************/
bool NN::train(TrainingSet tset)
{
  bool trained = false;
  for (int training_cycle = 1; training_cycle < NN_MAX_TRAIN_CYCLE; training_cycle++)
  {
    float error = 0.0;

    /******************************************************************
     * Cycle through each training pattern in the randomized order
     ******************************************************************/
    Logger::info("Cycle through each training pattern");

    int i = 0;
    vector<vector<float>>::iterator it;
    for (it = tset._ingress.begin(); it != tset._ingress.end(); it++, i++)
    {
      vector<float> ingress = *it;
      vector<float> target = tset._target.at(i);

      compute_hidden_layer_activations(ingress);
      error = compute_output_layer_activations_err(target, error);
      backpropagate();
      update_input_hidden_weights(ingress);
      update_hidden_hidden_weights();
      update_hidden_output_weights();

      Logger::info("trainingCycle: " + to_string(training_cycle) + " error = " + to_string(error) + " success = " + to_string(_success));
    }

    /******************************************************************
     * If error rate is less than pre-determined threshold then end
     ******************************************************************/
    if (error < _success)
    {
      printf("INFO: Training Set Solved!\n");
      trained = true;
      break;
    }
  }

  return trained;
}

void to_terminal(vector<float> ingress)
{
  Logger::info("showing results for debug purposes");
  vector<float>::iterator it;
  for (it = ingress.begin(); it != ingress.end(); it++)
  {
    Logger::info(to_string(*it) + ": " + to_string(*it));
  }
}

void NN::layer_activation(
  Layer &layer,
  vector<float> &ingress, 
  vector<vector<float>> &weights,
  const int in_node_sz,
  const int node_sz)
{
  for (int i = 0; i < node_sz; i++)
  {
    float accum = weights[in_node_sz][i];
    for (int j = 0; j < in_node_sz; j++)
    {
      accum += ingress[j] * weights[j][i];
    }
    layer._nodes[i] = 1.0 / (1.0 + exp(-accum));
  }
}

/******************************************************************
 * Compute hidden layer activations
 ******************************************************************/
void NN::compute_hidden_layer_activations(vector<float> ingress)
{
  Logger::info("Compute hidden layer activations");
  layer_activation(_hidden, ingress, _hidden_weights, _input_nodes_sz, _hidden_nodes_sz);
}

/******************************************************************
 * Compute output layer activations
 ******************************************************************/
void NN::compute_output_layer_activations()
{
  Logger::info("Compute output layer activations");
  layer_activation(_output, _hidden._nodes, _output_weights, _hidden_nodes_sz, _output_nodes_sz);
}

/******************************************************************
 * Compute output layer activations and calculate errors
 ******************************************************************/
float NN::compute_output_layer_activations_err(vector<float> target, float error)
{
  for (int i = 0; i < _output_nodes_sz; i++)
  {
    float accum = _output_weights[_hidden_nodes_sz][i];
    for (int j = 0; j < _hidden_nodes_sz; j++)
    {
      accum += _hidden._nodes[j] * _output_weights[j][i];
    }
    _output._nodes[i] = 1.0 / (1.0 + exp(-accum));
    _output._delta[i] = (target[i] - _output._nodes[i]) * _output._nodes[i] * (1.0 - _output._nodes[i]);
    error += 0.5 * (target[i] - _output._nodes[i]) * (target[i] - _output._nodes[i]);
  }
  Logger::info("Compute output layer activations and calculate errors: " + to_string(error));
  return error;
}

/******************************************************************
 * Backpropagate errors to hidden layer
 ******************************************************************/
void NN::backpropagate()
{
  for (int i = 0; i < _hidden_nodes_sz; i++)
  {
    float accum = 0.0;
    for (int j = 0; j < _output_nodes_sz; j++)
    {
      accum += _output_weights[i][j] * _output._delta[j];
    }
    _hidden._delta[i] = accum * _hidden._nodes[i] * (1.0 - _hidden._nodes[i]);
    Logger::info("INFO: Backpropagate errors to hidden layer");
  }
}

void NN::_update_weights(vector<vector<float>> &change_weights,
                         const int nodes_sz,
                         vector<vector<float>> &weights,
                         vector<float> ingress,
                         const int ingress_sz,
                         Layer layer)
{
  for (int i = 0; i < nodes_sz; i++)
  {
    change_weights[ingress_sz][i] = _learning_rate * layer._delta[i] + _momentum * change_weights[ingress_sz][i];
    weights[ingress_sz][i] += change_weights[ingress_sz][i];

    for (int j = 0; j < ingress_sz; j++)
    {
      change_weights[j][i] = _learning_rate * ingress[j] * layer._delta[i] + _momentum * change_weights[j][i];
      weights[j][i] += change_weights[j][i];
    }
  }
}

/******************************************************************
 * Update Input-->Hidden Weights.
 ******************************************************************/
void NN::update_input_hidden_weights(vector<float> ingress)
{
  Logger::info("Update Input-->Hidden Weights");
  _update_weights(
      _change_hidden_weights, // 0
      _hidden_nodes_sz,       // 1
      _hidden_weights,        // 2
      ingress,                // 3
      _input_nodes_sz,        // 4
      _hidden);               // 5
}

/******************************************************************
 * Update Hidden-->Hidden Weights.
 *
 * Update all hidden layers, last hidden layer will got to output
 * layer.
 ******************************************************************/
void NN::update_hidden_hidden_weights()
{
  Logger::info("Update Hidden-->Hidden Weights");
}

/******************************************************************
 * Update Hidden-->Output Weights
 ******************************************************************/
void NN::update_hidden_output_weights()
{
  Logger::info("Update Hidden-->Output Weights");
  _update_weights(
      _change_output_weights, // 0
      _output_nodes_sz,       // 1
      _output_weights,        // 2
      _hidden._nodes,         // 3
      _hidden_nodes_sz,       // 4
      _output);               // 5
}

Layer NN::predict(vector<float> ingress)
{
  compute_hidden_layer_activations(ingress);
  compute_output_layer_activations();

  return _output;
}