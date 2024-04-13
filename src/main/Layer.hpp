#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include "node.hpp"

using namespace std;

class Layer {
    public:
        vector<float> _nodes;
        int          _size;
};

#endif