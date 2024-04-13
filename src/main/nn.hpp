#ifndef nn_hpp
#define nn_hpp

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <random>
#include "Layer.hpp"
#include "Logger.hpp"
#include "TrainingSet.hpp"

using namespace std;

// #ifndef DEBUG_MODE
// #define RANDO 42
// #else
// #define RANDO float(( (random() * 100000) % 100) / 100)

#define RANDO nn_random()
#define NN_MAX_TRAIN_CYCLE 5
// #endif


class NN {
    private:
        size_t _input_nodes_sz;

        Layer  _hidden;
        size_t _hidden_nodes_sz;
        vector<vector<float> > _change_hidden_weights;
        vector<vector<float> > _hidden_weights;


        vector<vector<float> > _change_output_weights;
        vector<vector<float> > _output_weights;   

        float  _initial_weight_max;

    public:
        size_t _output_nodes_sz;
        Layer  _output;

        void setup(const size_t, 
                   const size_t, 
                   const float,
                   const size_t );
        void initialize_hidden();
        void initialize_output();
        void compute_hidden_layer_activations(vector<float>);
        void compute_output_layer_activations();
        void backpropagate();
        void update_inner_hidden_weights();
        void update_hidden_output_weights();

        void train(TrainingSet tset);
};

#endif