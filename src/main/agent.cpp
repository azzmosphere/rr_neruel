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
    _input_nodes_sz = config.input_nodes(_nid);
    _output_nodes_sz = config.output_nodes(_nid);
    _success = config.nn_success(_nid);
    _learning_rate = config.nn_learning_rate(_nid);
    _momentum  = config.nn_momentum(_nid);
    // _layers_sz = config.hidden_layers(_nid);

    for (size_t i = 0; i < (_layers_sz + 1); i++)
    {
        Logger::info("initialize neuron layers");
        if (i != _layers_sz) {
            // add bias to input nodes to get hidden layer size
            _layers.push_back(new RowVector((_layers_sz + 1)));
        }
        else 
        {
            _layers.push_back(new RowVector(_output_nodes_sz));
        }

        Logger::info("initialize cache and delta vectors");
        _change_weights.push_back(new RowVector(_layers.size()));
        _deltas.push_back(new RowVector(_layers.size()));

        Logger::info("initialize weights matrix");
        if (i > 0) 
        {
            // weights will be different 
            if (i > 0) {
                if (i != (_layers.size() + 1)) {
                    _weights.push_back(new Matrix())
                }
            }
            else 
            {

            }
        }
    }

}