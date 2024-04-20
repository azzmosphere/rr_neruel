/**
 * Read the configuration.
 */
#ifndef CONFIGYAML_HPP
#define CONFIGYAML_HPP

#include "yaml-cpp/yaml.h"
#include "config.hpp"

class ConfigYamlReader: public ConfigReader {
    public:
        void load_file(const string config);
};

#endif