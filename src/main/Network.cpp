#include "Network.hpp"

using namespace std;

void Network::initalize(
    const string nid,
    const size_t nhidden,
    const size_t ninodes,
    const size_t nhnodes,
    const size_t nonodes)
{
    Logger::info("initializing network:" + nid + " :" + std::string(" nhidden:") + to_string(nhidden) + std::string(" ninodes:") + to_string(ninodes) + std::string(" nhnodes:") + to_string(nhnodes) + std::string(" nonodes:") + to_string(nonodes));
    _nhidden = nhidden;
    _ninodes = ninodes;
    _nhnodes = nhnodes;
    _nonodes = nonodes;
    _nid = nid;

    Logger::info("initialize hidden layers");
    for (size_t i = 0; i < _nhidden; i++)
    {
        Logger::info("initalizing hidden layer " + to_string(i));
        _hidden[i].initialize(nhnodes, ninodes);
    }

    Logger::info("inialize output layer");
    _output.initialize(nonodes, nhnodes);

    Logger::info("network initalised");
}

void Network::train(TrainingSet tset)
{
    for (size_t trainingCycle = 1; trainingCycle < 5000; trainingCycle++)
    {
        float error = 0.0;

        Logger::info("Cycle through each training pattern");
        size_t pattern_count = tset._target.size();
        for (size_t p = 0; p < pattern_count; p++)
        {
            float ingress[_ninodes];
            for (size_t i = 0; i < _ninodes; i++)
            {
                ingress[i] = tset._ingress.at(p).at(i);
            }

            float target[_nonodes];
            for (size_t i = 0; i < _nonodes; i++)
            {
                target[i] = tset._target.at(p).at(i);
            }

            Layer egress = _output;
            for (size_t i = _nhidden; i > 0; i--)
            {
                _hidden[i].layer_activation(ingress, _ninodes);
                error = _output.output_activation(ingress, target, _nhnodes, error);
                _hidden[i].backpropagate(egress);
                egress = _hidden[i];
            }

            // Update Inner-->Hidden Weights
            for (size_t i = 0; i < _nhidden; i++)
            {
                _hidden[i].update_inner(ingress, _ninodes);
            }
            _output.update_inner(_hidden[_nhidden - 1]._nodes, _nhnodes);
        }

        Logger::info("trainingCycle: " + to_string(trainingCycle));

        if (error < NN_SUCCESS)
        {
            Logger::info("successfully trained");
            break;
        }       
    }
}


/**
 *  Perform prediction based on training.
 */
OutputLayer Network::predict(const float *input, const size_t sz) 
{

    float ingress[_nhnodes];
    bzero(ingress, sz);
    std::memcpy(ingress, input, sizeof(float) * sz);
    _hidden[0].layer_activation(ingress, sz);

    bzero(ingress, sz);
    std::memcpy(ingress, input, sizeof(float) * sz);   
    for (size_t i = 1; i < _nhidden; i++)
    {
        _hidden[i].layer_activation(ingress, _nhnodes);
         bzero(ingress, _nhnodes);
        std::memcpy(ingress, _hidden->_nodes, sizeof(float) * _nhnodes);
    }
    _output.layer_activation(ingress, _ninodes);
    return _output;
}