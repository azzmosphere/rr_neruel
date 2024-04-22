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
    /*
    *  creates a NN made up 
    *
    *  weights topology = {{{.15, .2}, {.25, .3}}, {{.4,.45},{.5,.55}}}
    *  biases           = {.35, .6}
    */
    void setup(vector<Matrix> weights, RowVector biases, vector<uint16_t> topology);

private:

 // hidden layer(s), and output
 // contains the activation values.  
vector<RowVector*> _neurons; 

 // all connecting weights
vector<Matrix*>    _weights; 

 // The BIAS layer.
RowVector         *_biases;  

};

#endif