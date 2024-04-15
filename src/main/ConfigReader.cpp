/**
 * Reads configuration file, and allows application to be configured. 
 */


#include "ConfigReader.hpp"


static inline YAML::Node retrieve_node(string key, YAML::Node node) 
{
    YAML::Node rv = node[key].as<YAML::Node>();
    return rv;
}


/**
 * Load configuration from input YAML file. 
 */
void ConfigReader::load_file(string config_file) {
    Logger::info("reading configuration file: " + config_file);
    YAML::Node config = YAML::LoadFile(trim(config_file));

    YAML::Node networks = config["networks"].as<YAML::Node>();
    
    for (YAML::iterator it = networks.begin(); it != networks.end(); ++it) {
        YAML::Node node = *it;
         
        _nn_success       = node["success"].as<float>();
        _nn_inital_weight = node["inital_weight"].as<float>();
        _nn_learning_rate = node["learning_rate"].as<float>();
        _nn_momentum      = node["momentum"].as<float>();

        _input_nodes  = retrieve_node("input", node)["nodes"].as<float>();
        _output_nodes = retrieve_node("output", node)["nodes"].as<float>();

        _hidden_nodes  = retrieve_node("hidden", node)["nodes"].as<float>();
        _hidden_layers = retrieve_node("hidden", node)["layers"].as<float>();
    }
}


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