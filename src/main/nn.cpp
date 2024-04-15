/**
 * Code to control the neural network.
 */

#include "nn.hpp"

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
float nn_random()
{
  // Truly random seed.
  std::mt19937 rng(std::random_device{}());

  // Avoid constructing distribution all the time
  std::uniform_int_distribution<> dist(0, 100);

  float r = float(dist(rng)) / 100.0f;

  return r;
}

// TODO: Deprecate this!!!!
void NN::setup(
    const size_t input_nodes_sz,
    const size_t hidden_nodes_sz,
    const float initial_weight_max,
    const size_t output_nodes_sz)
{
  _initial_weight_max = initial_weight_max;
  _input_nodes_sz = input_nodes_sz;
  _hidden_nodes_sz = hidden_nodes_sz;
  _output_nodes_sz = output_nodes_sz;

  _hidden_weights.resize(_input_nodes_sz + 1);
  _change_hidden_weights.resize(input_nodes_sz + 1);
  _hidden._delta.resize(_hidden_nodes_sz, 0);

  _output_weights.resize(_hidden_nodes_sz + 1);
  _change_output_weights.resize(_hidden_nodes_sz + 1);
  _output._delta.resize(_output_nodes_sz, 0);
  _output._nodes.resize(output_nodes_sz, 0);

  int i = 0;
  vector<vector<float>>::iterator it;
  _setup_change_weights_(_change_hidden_weights, _hidden_weights, _hidden_nodes_sz);

  i = 0;
  _setup_change_weights_(_change_output_weights, _output_weights, _output_nodes_sz);

  _hidden._nodes.resize(_hidden_nodes_sz, 0.);
}

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
void NN::train(TrainingSet tset)
{
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

      Logger::info("trainingCycle: " + to_string(training_cycle) + " error = " + to_string(error) + " success = " + to_string(_success));
    }
  }
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

/******************************************************************
 * Compute hidden layer activations
 ******************************************************************/
void NN::compute_hidden_layer_activations(vector<float> ingress)
{
  Logger::info("Compute hidden layer activations");
  for (int i = 0; i < _hidden_nodes_sz; i++)
  {
    float accum = _hidden_weights[_input_nodes_sz][i];
    for (int j = 0; j < _input_nodes_sz; j++)
    {
      accum += ingress[j] * _hidden_weights[j][i];
    }
    _hidden._nodes[i] = 1.0 / (1.0 + exp(-accum));
  }
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
 * 
 * Update this to cycle through each hidden layer, when hidden 
 * layers are added.
 ******************************************************************/
void NN::update_input_hidden_weights(vector<float> ingress)
{
  Logger::info("Update Input-->Hidden Weights");
  _update_weights(_change_hidden_weights, _hidden_nodes_sz, _hidden_weights, ingress, _input_nodes_sz, _hidden);
  to_terminal(_change_hidden_weights[0]);
}
