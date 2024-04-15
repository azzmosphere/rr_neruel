#ifndef nn_hpp
#define nn_hpp

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <random>
#include <map>
#include <string>
#include "Layer.hpp"
#include "Logger.hpp"
#include "TrainingSet.hpp"
#include "ConfigReader.hpp"

using namespace std;

// #ifndef DEBUG_MODE
// #define RANDO 42
// #else
// #define RANDO float(( (random() * 100000) % 100) / 100)

#define RANDO nn_random()
#define NN_MAX_TRAIN_CYCLE 5
// #endif

class NN
{
private:
    void _update_weights(vector<vector<float>> &change_weights,
                         const int nodes_sz,
                         vector<vector<float>> &weights,
                         vector<float> ingress,
                         const int ingress_sz,
                         Layer layer);

protected:
    size_t _input_nodes_sz;

    Layer _hidden;
    size_t _hidden_nodes_sz;
    vector<vector<float>> _change_hidden_weights;
    vector<vector<float>> _hidden_weights;

    vector<vector<float>> _change_output_weights;
    vector<vector<float>> _output_weights;

    float _initial_weight_max;
    float _success;
    float _learning_rate;
    float _momentum;

    string _nid;

public:
    size_t _output_nodes_sz;
    Layer _output;

    // Deprecate this
    void setup(const size_t,
               const size_t,
               const float,
               const size_t);

    void setup(string nid, ConfigReader config);
    void initialize_hidden();
    void initialize_output();
    void compute_hidden_layer_activations(vector<float>);
    float compute_output_layer_activations_err(vector<float>, float);
    void backpropagate();
    void update_inner_hidden_weights(vector<float>);
    void update_hidden_hidden_weights();
    void update_hidden_output_weights();

    void train(TrainingSet tset);
};

#endif