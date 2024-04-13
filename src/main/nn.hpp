#ifndef nn_hpp
#define nn_hpp

#include <vector>
#include <math.h>
#include <stdlib.h>
#include "Layer.hpp"

using namespace std;

#define RANDO float((random() % 100) / 100)

class NN {
    private:
        Layer _hidden;
        size_t _hidden_nodes_sz;
        size_t _input_nodes_sz;
        vector<vector<float> > _change_hidden_weights;
        vector<vector<float> > _hidden_weights;
        float  _initial_weight_max;

    public:
       
        Layer _output;
        void setup(const size_t, const size_t, const float);
        void initialize_hidden();
        void initialize_output();
        void compute_hidden_layer_activations();
        void compute_output_layer_activations();
        void backpropagate();
        void update_inner_hidden_weights();
        void update_hidden_output_weights();
};

#endif