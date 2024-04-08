#include "Layer.hpp"

void Layer::initialize(size_t nsize, size_t inodes) {
    _size = nsize;

    Logger::info("Initialize HiddenWeights and ChangeHiddenWeights");
    for (size_t i = 0; i < _size; i++)
    {
        for (size_t j = 0; j <= inodes; j++)
        {
            _change_weights[j][i] = 0.0;
            float rando = float(random(100)) / 100;
            _weights[j][i] = 2.0 * (rando - 0.5) * NN_INITIAL_WEIGHT;
        }
    }
}