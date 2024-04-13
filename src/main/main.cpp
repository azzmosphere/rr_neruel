#include "nn.hpp"


const float NN_INITIAL_WEIGHT = 0.5;
NN network;

void setup() {
    network.setup(7, 8, NN_INITIAL_WEIGHT, 4);
    network.initialize_hidden();
    network.initialize_output();
}

void train(const string tset_file) {
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