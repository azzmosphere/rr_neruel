/**
 * Read YAML configuration and return variables that can be used to configure networks (etc) 
 */

#ifndef CONFIGR_HPP
#define CONFIGR_HPP

#include <string>

#include "rrutils.hpp"

using namespace std;

class ConfigReader  {

    public:
        // given the nid get the hidden layers.
        virtual unsigned int hidden_layers(const string nid);

        // given nid get hidden nodes
        virtual unsigned int hidden_nodes(const string nid);
        virtual unsigned int input_nodes(const string nid);
        virtual unsigned int output_nodes(const string nid);

        virtual float nn_success(const string nid);        // success rate.
        virtual float nn_learning_rate(const string nid);  // Neural Network Learning Rate
        virtual float nn_momentum(const string nid);
        virtual float nn_inital_weight(const string nid);

    
    protected:
        unsigned int _hidden_layers = 0;
        unsigned int _hidden_nodes = 0;
        unsigned int _input_nodes  = 0;
        unsigned int _output_nodes = 0;

        float _nn_success = 0;        // success rate.
        float _nn_learning_rate = 0;  // Neural Network Learning Rate
        float _nn_momentum = 0;
        float _nn_inital_weight = 0;
        
};

#endif