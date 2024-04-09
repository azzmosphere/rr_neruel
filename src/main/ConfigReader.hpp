/**
 * Read YAML configuration and return variables that can be used to configure networks (etc) 
 */

#ifndef CONFIGREADER_HPP
#define CONFIGREADER_HPP

#include "FileReader.hpp"
#include "Logger.hpp"
#include <string>
#include "yaml-cpp/yaml.h"

using namespace std;

class ConfigReader : public FileReader {

    public:
        // given the nid get the hidden layers.
        unsigned int hidden_layers(const string nid);

        // given nid get hidden nodes
        unsigned int hidden_nodes(const string nid);
        unsigned int input_nodes(const string nid);
        unsigned int output_nodes(const string nid);

        float nn_success(const string nid);        // success rate.
        float nn_learning_rate(const string nid);  // Neural Network Learning Rate
        float nn_momentum(const string nid);
        float nn_inital_weight(const string nid);


        void load_file(const string config);
    
    private:
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