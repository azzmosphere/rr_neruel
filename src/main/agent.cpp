/**
 * Implementation of Machine Learning, Artifical Neruel Network agent.
 */

#include "agent.hpp"

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
void Agent::setup(string nid, ConfigReader config)
{
    _nid = nid;
    _initial_weight_max = config.nn_inital_weight(_nid);
    _success = config.nn_success(_nid);
    _learning_rate = config.nn_learning_rate(_nid);
    _momentum = config.nn_momentum(_nid);

    _input_nodes_sz = config.input_nodes(_nid);
    _output_nodes_sz = config.output_nodes(_nid);
    _layers_sz = config.hidden_layers(_nid);
    

    for (size_t i = 0; i < _units_per_layer.size() - 1; ++i)
    {
        // size_t in_channels{_input_nodes_sz};
        // size_t out_channels{_output_nodes_sz};

        // // initialize to random Gaussian
        // auto W = lynalg::mtx<T>::randn(out_channels, in_channels);
        // weight_matrices.push_back(W);

        // auto b = lynalg::mtx<T>::randn(out_channels, 1);
        // bias_vectors.push_back(b);

        // activations.resize(units_per_layer.size());
    }
}