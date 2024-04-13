#include "nn.hpp"


const float NN_INITIAL_WEIGHT = 0.5;

int main() 
{
    float NN_INITIAL_WEIGHT = 0.5;

    NN network;
    network.setup(2, 3, NN_INITIAL_WEIGHT);

    network.initialize_hidden();
    return 0;
}