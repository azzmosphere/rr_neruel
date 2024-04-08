#include "OutputLayer.hpp"



/******************************************************************
 * Compute output layer activations and calculate errors
 ******************************************************************/
float OutputLayer::output_activation(float ingress[], float target[], size_t isize, float error)
{
    Logger::info("Compute output layer activations and calculate error");
    for (size_t i = 0; i < _size; i++)
    {
        float accum = _weights[isize][i];
        for (size_t j = 0; j < _size; j++)
        {
            accum += ingress[j] * _weights[j][i];
        }
        _nodes[i] = 1.0 / (1.0 + exp(-accum));
        _delta[i] = (target[i] - _nodes[i]) * _nodes[i] * (1.0 - _nodes[i]);
        error += 0.5 * (target[i] - _nodes[i]) * (target[i] - _nodes[i]);
    }
    return error;
}
