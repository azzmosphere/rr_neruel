#ifndef NETWORK_HPP
#define NETWORK_HPP


#include <stdlib.h>
#include "Logger.hpp"
#include "Layer.hpp"
#include "OutputLayer.hpp"
#include "TrainingSet.hpp"

#define NN_SUCCESS 0.0004
#define NN_MAX_LAYERS 2

class Network {
    public:
        void initalize(
            const string nid,
            const size_t nhidden, 
            const size_t ninodes,
            const size_t nhnodes, 
            const size_t nonodes);

        void train(TrainingSet);

    private:
        size_t _nhidden;
        size_t _ninodes;
        size_t _nhnodes; 
        size_t _nonodes;  
        string _nid;

    protected:
       Layer _hidden[NN_MAX_LAYERS];
       OutputLayer _output; 
};

#endif