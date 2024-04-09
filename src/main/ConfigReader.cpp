/**
 * Reads configuration file, and allows application to be configured. 
 */


#include "ConfigReader.hpp"

void ConfigReader::load_file(string config_file) {
    Logger::info("reading configuration file: " + config_file);
    YAML::Node config = YAML::LoadFile(trim(config_file));

    YAML::Node networks = config["networks"].as<YAML::Node>();
    
    for (YAML::iterator it = networks.begin(); it != networks.end(); ++it) {
        YAML::Node network = *it;
        
       _nn_success       = network["success"].as<float>();
       _nn_inital_weight = network["inital_weight"].as<float>();
       _nn_learning_rate = network["learning_rate"].as<float>();
       _nn_momentum      = network["momentum"].as<float>();
    }
}
