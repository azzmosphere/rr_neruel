#ifndef OUTPUTLAYER_HPP
#define OUTPUTLAYER_HPP

#include "Layer.hpp"

class OutputLayer : public Layer
{

    public:
        /******************************************************************
        * Compute output layer activations and calculate errors
        ******************************************************************/
        float output_activation(float ingress[], float target[], size_t isize, float);
};

#endif