/**
 * Code to control the neural network.  
 */

#include "nn.hpp"



// Private Macros
#define _initialize_(_nodes_sz_, _input_nodes_sz_, _change_weights_, _weights_)  \
  for (int i = 0; i < _nodes_sz_; i++) \
  { \
    for (int j = 0; j <= _input_nodes_sz_; j++) \
    { \
      _change_weights_[j][i] = 0.0; \
      _weights_[j][i] = 2.0 * (RANDO - 0.5) * _initial_weight_max; \
    } \
  }

#define _setup_change_weights_(_x_, _y_, _s_)  for (it = _x_.begin(); it != _x_.end(); it++, i++) \
  { \
    vector<float> f, y; \
    f.resize(_s_); \
    y.resize(_s_); \
    _x_.at(i) = f; \
    _y_.at(i) = y; \
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

void NN::setup(
    const size_t input_nodes_sz,
    const size_t hidden_nodes_sz,
    const float initial_weight_max,
    const size_t output_nodes_sz
)
{
  _initial_weight_max = initial_weight_max;
  _input_nodes_sz = input_nodes_sz;
  _hidden_nodes_sz = hidden_nodes_sz;
  _output_nodes_sz = output_nodes_sz;

  _hidden_weights.resize(_input_nodes_sz + 1);
  _change_hidden_weights.resize(input_nodes_sz + 1);

  _output_weights.resize(_hidden_nodes_sz + 1);
  _change_output_weights.resize(_hidden_nodes_sz + 1);


  int i = 0;
  vector<vector<float>>::iterator it;
  _setup_change_weights_(_change_hidden_weights, _hidden_weights, _hidden_nodes_sz);

  i = 0;
  _setup_change_weights_(_change_output_weights, _output_weights, _output_nodes_sz);
}



//TODO: debug code
void to_terminal(vector<vector<float> > _hidden_weights)
{
    int i = 0;

    vector<vector<float>>::iterator it;
    for (it = _hidden_weights.begin(); it != _hidden_weights.end(); it++, i++) 
    {
        vector<float> v = _hidden_weights.at(i);
        vector<float>::iterator iit;
        int j = 0;
        for (iit = v.begin(); iit != v.end(); iit++, j++) 
        {
            Logger::info(to_string(i) + ": " + to_string(v.at(j)));
        }
    }
}


/******************************************************************
 * Initialize HiddenWeights and ChangeHiddenWeights
 ******************************************************************/
void NN::initialize_hidden()
{
  Logger::info("Initialize HiddenWeights and ChangeHiddenWeights");

  _initialize_(_hidden_nodes_sz, _input_nodes_sz, _change_hidden_weights, _hidden_weights);

  //TODO :debug code
  to_terminal(_hidden_weights);
}

/******************************************************************
 * Initialize OutputWeights and ChangeOutputWeights
 ******************************************************************/
void NN::initialize_output()
{
    Logger::info("Initialize OutputWeights and ChangeOutputWeights");
    _initialize_(_output_nodes_sz, _hidden_nodes_sz, _change_output_weights, _output_weights);
     to_terminal(_output_weights);
}