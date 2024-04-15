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

    return 0;
}