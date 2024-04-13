#include "nn.hpp"

void NN::setup(
    const size_t input_nodes_sz, 
    const size_t hidden_nodes_sz,
    const float  initial_weight_max) 

{
    _initial_weight_max = initial_weight_max;
    _input_nodes_sz = input_nodes_sz;
    _hidden_nodes_sz = hidden_nodes_sz;

    _hidden_weights.resize(_input_nodes_sz + 1);
    _change_hidden_weights.resize(input_nodes_sz + 1);

    int i = 0;

    vector<vector<float> >::iterator it;
    for (it = _change_hidden_weights.begin(); it != _change_hidden_weights.end(); it++, i++) {
        vector<float> f, y;
        f.resize(hidden_nodes_sz);
        y.resize(hidden_nodes_sz);
        _change_hidden_weights.at(i) = f;
        _hidden_weights.at(i) = y;
    }
}

/******************************************************************
 * Initialize HiddenWeights and ChangeHiddenWeights
 ******************************************************************/
void NN::initialize_hidden()
{
    Logger::info("Initialize HiddenWeights and ChangeHiddenWeights");

    for (int i = 0; i < _hidden_nodes_sz; i++)
    {
        for (int j = 0; j <= _input_nodes_sz; j++)
        {
            _change_hidden_weights[j][i] = 0.0;
            _hidden_weights[j][i] = 2.0 * (RANDO - 0.5) * _initial_weight_max;
        }
    }
}

// /******************************************************************
//  * Initialize OutputWeights and ChangeOutputWeights
//  ******************************************************************/
// void NN::initialize_output()
// {
//   printf("INFO: Initialize OutputWeights and ChangeOutputWeights\n"); 
//   for (int i = 0; i < OutputNodes; i++)
//   {
//     for (int j = 0; j <= _hidden_nodes_sz; j++)
//     {
//       ChangeOutputWeights[j][i] = 0.0;
//       OutputWeights[j][i] = 2.0 * (RANDO - 0.5) * InitialWeightMax;
//     }
//   }
// }