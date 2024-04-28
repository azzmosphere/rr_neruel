/**
 * Extends Layer, so that multiple hidden layers can be support,  this is done by
 * adding hidden_weights, and change_hidden_weights to the netowrk. 
 */

#ifndef HIDDEN_HPP
#define HIDDEN_HPP
#include "Layer.hpp"

class Hidden : public Layer {
private:
    vector<vector<float>> _change_weights;
    vector<vector<float>> _weights;

    friend class NN;
};


#endif