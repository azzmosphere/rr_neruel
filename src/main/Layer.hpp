//TODO: Deprecated

#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

using namespace std;

class Layer {
    public:
        vector<float> _nodes;
        vector<float> _delta;
};

#endif