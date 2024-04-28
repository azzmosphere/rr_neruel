/*************************************************************************
* Ryder Robot Neural Network algorithm.
*
*
**************************************************************************/

#ifndef RR_NN_HPP
#define RR_NN_HPP

#include <vector>
#include <Eigen/Core>
#include <Eigen/Eigen>

#include "Logger.hpp"


typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;

using namespace std;

class RrNn {
public:
    void setup(vector<Matrix*> weights, RowVector biases, vector<size_t> topology);
    vector<float> predict(vector<float> input);
    vector<float> forward_propagate(vector<float> input, size_t l);
    
    // Recompute the distance to the error, assigning relavent deltas.  The target should be an ideal
    // outcome of what task the agent is performing.
    //
    // actual vector is the one recieved from the micro processor once action is sent.
    // expected vector is the ideal outcome.
    float compute_error(vector<float> expected, vector<float> target);

    float _error;

private:

    // hidden layer(s), and output
    // contains the activation values.  
    Matrix          _neurons;   // AKA activations
    vector<float>   _deltas;    // results of the delta rule.
    vector<float>   _biases;    // The BIAS layer.
    vector<Matrix*> _weights;   // all connecting weights
    vector<size_t>  _topology;  // contains size of each layer.

};

#endif