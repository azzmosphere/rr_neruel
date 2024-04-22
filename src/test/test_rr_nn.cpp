#include "rr_nn.hpp"

RrNn nn;

int main()
{
    vector<Matrix> weights;
    Matrix i_h(3, 2);
    i_h.row(0) << .15, .2;
    i_h.row(1) << .25, .3;

    Matrix h_o(3, 2);
    h_o.row(0) << .40, .45;
    h_o.row(1) << .50, .55;    

    weights.push_back(i_h);
    weights.push_back(h_o);

    RowVector biases(2);
    biases << .35, .6;

    // two input layers, two hidden, two output.
    vector<uint16_t> topology = {2, 2, 2};

    nn.setup(weights, biases, topology);
}