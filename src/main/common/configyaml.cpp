/*****************************************************************
 * Reads configuration from YAML file.
 *****************************************************************/

#include "configyaml.hpp"

static inline YAML::Node retrieve_node(string key, YAML::Node node) 
{
    YAML::Node rv = node[key].as<YAML::Node>();
    return rv;
}

/**
 * Load configuration from input YAML file. 
 */
void ConfigYamlReader::load_file(string config_file) {
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