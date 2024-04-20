#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <eigen3/Eigen/Eigen>

#include "config.hpp"

class Agent {

public:
    void setup(ConfigReader conf);
    void forward_propagate(RowVector& input);
    void backward_propagate(RowVector& output);
    void train(TrainingSet tset);

protected:
    flaot  compute_activations_err(RowVector& input, float err);
    floats update_weights();

private:
    string _nid;
    float _initial_weight_max;
    float _success;
    float _learning_rate; // sometimes referred to as epsilon
    float _momentum;

    vector<Matrix*>    _weights;
    vector<RowVector*> _deltas;
    vector<RowVector*> _change_weights;
    vector<RowVector*> _layers;
};
#endif