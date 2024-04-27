#include "rr_nn.hpp"

float _sigmoid(float x)
{
    return 1.0f / (1 + exp(-x));
}

// computes the delta rule.
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
    _deltas.resize(topology.size(), i);
    _topology.clear();
    for (auto &i : topology)
    {
        _topology.push_back(i);
    }

    // print topology
    Logger::info("_topology[0] = " + to_string(_topology[0]));
}

/***********************************************************************************************
 * input comming in,
 * which layer position.
 * net_{h1} = w_1 * i_1 + w_2 * i_2 + b_1 * 1
 *
 ***********************************************************************************************/
vector<float> RrNn::forward_propagate(vector<float> ingress, const size_t l)
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

/***********************************************************************************************
 * expected result is an ideal state,  actual is the state returned.
 * 
 * Expected can be considered a reward,  and the actual is how far the agent is from achieving
 * that reward.  With the actual being the state genertated as a result of the actions.
 ***********************************************************************************************/
float RrNn::compute_error(vector<float> expected, vector<float> actual)
{
    for (size_t i = 0; i < actual.size(); i++)
    {
        _deltas[i] = (expected[i] - actual[i]) * actual[i] * (1.0 - actual[i]);
        _error += 0.5 * (expected[i] - actual[i]) * (expected[i] - actual[i]);
    }
    return _error;
}

vector<float> RrNn::predict(vector<float> input)
{
    vector<float> r;
    return r;
}