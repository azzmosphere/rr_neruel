#include "rr_nn.hpp"


/***********************************************************
 *  Create network based on the topology given.
 * 
 *  weights : weight to connecting nodes.
 *  
 ***********************************************************/
void RrNn::setup(vector<Matrix> weights, RowVector biases, vector<uint16_t> topology)
{
    Logger::info("creating weights max");
    for (auto &w : weights) {
        _weights.push_back(&w);
    }

    _biases = &biases;

    for (auto &i : topology)
    {
        RowVector r(i);
        _neurons.push_back(&r);
    }
}

