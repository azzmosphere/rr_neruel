#include "Layer.hpp"

void Layer::initialize(size_t nsize, size_t inodes)
{
    _size = nsize;

    Logger::info("Initialize HiddenWeights and ChangeHiddenWeights");
    for (size_t i = 0; i < _size; i++)
    {
        for (size_t j = 0; j <= inodes; j++)
        {
            _change_weights[j][i] = 0.0;
            float rando = float(random(100)) / 100;
            _weights[j][i] = 2.0 * (rando - 0.5) * NN_INITIAL_WEIGHT;
        }
    }
}

/******************************************************************
 * Compute hidden layer activations
 ******************************************************************/
void Layer::layer_activation(float ingress[], size_t isize)
{
    Logger::info("Compute hidden layer activations");
    for (size_t i = 0; i < _size; i++)
    {
        float accum = _weights[isize][i];
        for (size_t j = 0; j < isize; j++)
        {
            // only want the initial vector,  not [p][j] or y x
            accum += ingress[j] * _weights[j][i];
        }
        _nodes[i] = 1.0 / (1.0 + exp(-accum));
    }
}