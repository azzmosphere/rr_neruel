#include "nn.hpp"


const float NN_INITIAL_WEIGHT = 0.5;
NN network;

void setup() {
    network.setup(7, 8, NN_INITIAL_WEIGHT, 4);
    network.initialize_hidden();
    network.initialize_output();
}

void train() {
    network.train();
}

int main() 
{
    setup();
    return 0;
}