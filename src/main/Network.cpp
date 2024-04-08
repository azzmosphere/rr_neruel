#include "Network.hpp"

void Network::initalize(
    const size_t nid,
    const size_t nhidden,
    const size_t ninodes,
    const size_t nhnodes,
    const size_t nonodes)
{
    Logger::info("initializing network:" + to_string(nid) + " :" + std::string(" nhidden:") + to_string(nhidden) + std::string(" ninodes:") + to_string(ninodes) + std::string(" nhnodes:") + to_string(nhnodes) + std::string(" nonodes:") + to_string(nonodes));
    _nhidden = nhidden;
    _ninodes = ninodes;
    _nhnodes = nhnodes;
    _nonodes = nonodes;
    _nid = nid;

    Logger::info("initialize hidden layers");
    _hidden.initialize(nhnodes, ninodes);

    Logger::info("inialize output layer");
    _output.initialize(nonodes, nhnodes);

    Logger::info("network initalised");
}

void Network::train(TrainingSet tset)
{
    for (size_t trainingCycle = 1; trainingCycle < 3; trainingCycle++)
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
        }
    }
}