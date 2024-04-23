#include "rr_nn.hpp"

float _sigmoid(float x)
{
    return 1.0f / (1 + exp(-x));
}

float _d_sigmoid(float x)
{
    return (x * (1 - x));
}

/***********************************************************
 *  Create network based on the topology given.
 *
 *  weights : weight to connecting nodes.
 *
 ***********************************************************/
void RrNn::setup(vector<Matrix *> weights, RowVector biases, vector<size_t> topology)
{
    Logger::info("adding weights");
    for (auto &w : weights)
    {
        _weights.push_back(w);
    }

    Logger::info("creating biasses");
    _biases.resize(biases.size());
    uint16_t i = 0;
    for (auto &b : biases)
    {
        _biases[i++] = b;
    }

    Logger::info("creating neurons");
    i = *max_element(topology.begin(), topology.end());

    _neurons.resize(topology.size(), i);
    _topology.clear();
    for (auto &i : topology)
    {
        _topology.push_back(i);
    }

    // print topology
    Logger::info("_topology[0] = " + to_string(_topology[0]));
}

// void NN::layer_activation(
//   Layer &layer,
//   vector<float> &ingress,
//   vector<vector<float>> &weights,
//   const int in_node_sz,
//   const int node_sz)
// {
//   for (int i = 0; i < node_sz; i++)
//   {
//     float accum = weights[in_node_sz][i];
//     for (int j = 0; j < in_node_sz; j++)
//     {
//       accum += ingress[j] * weights[j][i];
//     }
//     layer._nodes[i] = 1.0 / (1.0 + exp(-accum));
//   }
// }

/***********************************************************************************************
 * input comming in,
 * which layer position.
 * net_{h1} = w_1 * i_1 + w_2 * i_2 + b_1 * 1
 *
 ***********************************************************************************************/
vector<float> RrNn::forward_propagate(vector<float> ingress, size_t l)
{
    size_t node_sz = _topology.at(l);
    size_t in_node_sz = (l == 0) ? ingress.size() : _topology.at(l - 1);
    std::vector<float> vec;

    for (size_t i = 0; i < node_sz; i++)
    {
        // add the layer bias to the current node.
        float accum = _biases.at(l);
        for (size_t j = 0; j < in_node_sz; j++)
        {
            accum += ingress.at(j) * _weights.at(l)->coeff(j, i);
        }
        _neurons(l, i) = _sigmoid(accum);
        vec.push_back(_neurons(l, i));
    }
    return vec;
}

vector<float> RrNn::predict(vector<float> input)
{
    vector<float> r;
    return r;
}