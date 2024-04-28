/**************************************************************************
 * Each neruel network can be considered an agent, they can be changed to 
 * perform a specitic task.
 **************************************************************************/

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
#include "config.hpp"

using namespace std;

#ifndef TEST_MODE
#define RANDO nn_random()
#define NN_MAX_TRAIN_CYCLE 2147483647
#else
#define RANDO 42
#define NN_MAX_TRAIN_CYCLE 5
#endif

class NN
{
private:
    void _update_weights(vector<vector<float>> &change_weights,
                         const int nodes_sz,
                         vector<vector<float>> &weights,
                         vector<float> ingress,
                         const int ingress_sz,
                         Layer layer);
    
    void layer_activation(
        Layer &layer,
        vector<float> &ingress, 
        vector<vector<float>> &weights,
        const int in_node_sz,
        const int node_sz);

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

    void setup(string nid, ConfigReader config);
    void initialize_hidden();
    void initialize_output();
    
    void compute_hidden_layer_activations(vector<float>);
    void compute_output_layer_activations();
    float compute_output_layer_activations_err(vector<float>, float);
    
    void backpropagate();
    void update_input_hidden_weights(vector<float>);
    void update_hidden_hidden_weights();
    void update_hidden_output_weights();

    /*************************************************************************
     * return true if training is successful, otherwise false. If training 
     * fails then do not perform predictions,  model will need ot be 
     * re-trained.
     *************************************************************************/
    bool train(TrainingSet tset);
    Layer predict(vector<float>);
};

#endif