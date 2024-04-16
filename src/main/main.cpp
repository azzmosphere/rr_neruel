#include "nn.hpp"


const float NN_INITIAL_WEIGHT = 0.5;
NN network;
ConfigReader config;


// Perform any network(s) configuration, inject config file,  
// add MPIO
void setup() 
{
    config.load_file("/Users/newuser/projects/rr_neruel/resources/etc/config.yaml");
    network.setup("nid0", config);
    network.initialize_hidden();
    network.initialize_output();
}

// Need to get a file format going for training sets.  Training should happen, here for each network.
void train(const string tset_file) 
{
    TrainingSet tset;
    tset.deserialize(tset_file);
    network.train(tset);
}

int main() 
{
    setup();

    train("/Users/newuser/projects/rr_neruel/resources/training/training-set.0.json");

    // Perform some predictions to finish off the testing.
    vector<float> ingress = {1, 1, 1, 0, 0, 0, 0};
    network.predict(ingress);

    for (int i = 0; i < network._output_nodes_sz; i++) {
        Logger::info("col " + to_string(i) + ": " + to_string(network._output._nodes.at(i)));
    }

    return 0;
}