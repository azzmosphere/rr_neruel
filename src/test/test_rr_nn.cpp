#include "rr_nn.hpp"
using namespace std;

RrNn nn;
vector<Matrix*>  weights;
RowVector        biases;
vector<size_t> topology;


int main()
{
    
    weights.resize(8);
    weights.at(0) = new Matrix(2,2);

    // Layer, row, col

    // w1 
    weights.at(0)->row(0).col(0) << .15f;
    // w2
    weights.at(0)->row(0).col(1) << .2f;
    // w3
    weights.at(0)->row(1).col(0) << .25f;
    // w4
    weights.at(0)->row(1).col(1) << .3f;

    weights.at(1) = new Matrix(2,2);
    // w5 
    weights.at(1)->row(0).col(0) << .4f;
    // w6
    weights.at(1)->row(0).col(1) << .45f;
    // w7
    weights.at(1)->row(1).col(0) << .5f;
    // w8
    weights.at(1)->row(1).col(1) << .55f;  

    cout << "[i1] -" << weights.at(0)->row(0).col(0) << "-> [h1] -" << weights.at(1)->row(0).col(0) << "-> [o1]"  << endl;
    cout << "     \\" << weights.at(0)->row(1).col(0)  << endl;
    cout << "         \\" << endl;
    cout << "[i2] -" << weights.at(0)->row(1).col(1) << "-> [h1] -" << weights.at(1)->row(1).col(1) << "-> [o1]"  << endl;

    // Biases, each bias will match a specific layer
    biases.resize(2);
    biases << .35, .6;


    // Network topology
    topology.clear();
    topology.push_back(2);
    topology.push_back(2);

    nn.setup(weights, biases, topology);

    vector<float> input;
    input.clear();
    input.push_back(.05); 
    input.push_back(.1);
    vector<float> result = nn.forward_propagate(input, 0);

    Logger::info("stop here:" + to_string(result.at(0)));
    Logger::info("stop here:" + to_string(result.at(1)));

    result = nn.forward_propagate(result, 1);
    Logger::info("stop here:" + to_string(result.at(0)));
    Logger::info("stop here:" + to_string(result.at(1)));

}