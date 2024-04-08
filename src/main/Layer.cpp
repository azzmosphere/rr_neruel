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

/******************************************************************
 * Backpropagate errors to hidden layer
 ******************************************************************/
void Layer::backpropagate(Layer egress)
{
    Logger::info("Backpropagate errors to hidden layer");

    for (size_t i = 0; i < _size; i++)
    {
        float accum = 0.0;
        for (size_t j = 0; j < egress._size; j++)
        {
            accum += egress._weights[i][j] * egress._delta[j];
        }
        _delta[i] = accum * _nodes[i] * (1.0 - _nodes[i]);
    }
}

/******************************************************************
 * Update Inner-->Hidden Weights
 ******************************************************************/
void Layer::update_inner(float ingress[], size_t isize)
{
    Logger::info("Update Inner-->Hidden Weights");
    for (size_t i = 0; i < _size; i++)
    {
        _change_weights[isize][i] = NN_LEARNING_RATE * _delta[i] + NN_MOMENTUM * _change_weights[isize][i];
        _weights[isize][i] += _change_weights[isize][i];
        for (size_t j = 0; j < isize; j++)
        {
            _change_weights[j][i] = NN_LEARNING_RATE * ingress[j] * _delta[i] + NN_MOMENTUM * _change_weights[j][i];
            _weights[j][i] += _change_weights[j][i];
        }
    }
}