/**
 * Implementation of Machine Learning, Artifical Neruel Network agent.
 * 
 * Aimed to support multiple hidden layers,  and based largly on the work by Lyndon Duong 
 * (see https://www.lyndonduong.com/mlp-build-cpp/)
 */

#include "agent.hpp"


/**
 * Creates the tapology that will be used to configure agent.
 */
 void Agent::create_topology()
{
    Logger::info("creating toplogy for agent " + _nid);
    _units_per_layer.clear();
    _units_per_layer.push_back(_input_nodes_sz);

    for (size_t i = 0; i < _layers_sz; i++)
    {
        // each hidden layer is the same size as input layer + 1 extra neuron for bias.
        _units_per_layer.push_back(_input_nodes_sz + 1);
    }
     _units_per_layer.push_back(_output_nodes_sz);
}

/********************************************************
 * setup method.
 *
 * The tapology variable used in the example is something like this
 * NeuralNetwork n({ 2, 3, 1 });
 *
 * Assuming that translates to 2 nodes in input, 3 nodes in
 * hidden layer,  and 1 node for output,  which should solve
 * a xor test.
 ********************************************************/
void Agent::setup(string nid, ConfigReader *config)
{
    _nid = nid;
    _initial_weight_max = config->nn_inital_weight(_nid);
    _success            = config->nn_success(_nid);
    _learning_rate      = config->nn_learning_rate(_nid);
    _momentum           = config->nn_momentum(_nid);

    _input_nodes_sz  = config->input_nodes(_nid);
    _output_nodes_sz = config->output_nodes(_nid);
    _layers_sz       = config->hidden_layers(_nid);
    
    create_topology();

    for (size_t i = 0; i < _units_per_layer.size() - 1; ++i)
    {
        size_t in_channels{_units_per_layer[i]};
        size_t out_channels{_units_per_layer[i+1]};

        // initialize to random Gaussian
        // auto W = lynalg::mtx<T>::randn(out_channels, in_channels);
        // weight_matrices.push_back(W);

        // auto b = lynalg::mtx<T>::randn(out_channels, 1);
        // bias_vectors.push_back(b);

        // activations.resize(units_per_layer.size());
    }
}