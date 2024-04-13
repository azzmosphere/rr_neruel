#include "nn.hpp"


const float NN_INITIAL_WEIGHT = 0.5;

int main() 
{
    NN network;
    network.setup(2, 3, NN_INITIAL_WEIGHT, 1);

    network.initialize_hidden();
    network.initialize_output();
    return 0;
}