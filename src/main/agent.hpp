/*******************************************************************************************************************
 * References algebra logic provided by Eigen (see https://eigen.tuxfamily.org/dox-devel/group__QuickRefPage.html)
 *******************************************************************************************************************/

#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <Eigen/Core>
#include <Eigen/Eigen>

#include "TrainingSet.hpp"
#include "rrutils.hpp"
#include "config.hpp"
#include "Logger.hpp"

// Consider everything a float therefore use row vectors that are onluy of type float.
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;

class Agent {

public:
    void setup(string nid, ConfigReader conf);
    void forward_propagate(RowVector& input);
    void backward_propagate(RowVector& output);
    void train(TrainingSet tset);

protected:
    float compute_activations_err(RowVector& input, float err);
    float update_weights();

private:
    size_t _output_nodes_sz;
    size_t _input_nodes_sz;
    size_t _layers_sz;

    string _nid;
    float _initial_weight_max;
    float _success;
    float _learning_rate; // sometimes referred to as epsilon
    float _momentum;

    vector<RowVector*> _change_weights; // AKA cache
    vector<Matrix*>    _weights;
    vector<RowVector*> _deltas;
    vector<RowVector*> _layers;
};
#endif