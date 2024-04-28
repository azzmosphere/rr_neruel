/**
 * Reads configuration file, and allows application to be configured. 
 */


#include "config.hpp"


 unsigned int ConfigReader::hidden_layers(const string nid) {
    return _hidden_layers;
 }

unsigned int ConfigReader::hidden_nodes(const string nid) {
    return _hidden_nodes;
}

unsigned int  ConfigReader::input_nodes(const string nid) {
    return _input_nodes;
}

unsigned int ConfigReader::output_nodes(const string nid) {
    return _output_nodes;
}

float ConfigReader::nn_inital_weight(const string nid) {
    return _nn_inital_weight;
}

float ConfigReader::nn_success(const string nid) {
    return _nn_success;
}

float ConfigReader::nn_learning_rate(const string nid) {
    return _nn_learning_rate;
}

float ConfigReader::nn_momentum(const string nid) {
    return _nn_momentum;
}