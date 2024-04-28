/**
 * Implementation of Machine Learning, Artifical Neruel Network agent.
 *
 * Aimed to support multiple hidden layers,  and based largly on the work by Lyndon Duong
 * (see https://www.lyndonduong.com/mlp-build-cpp/)
 */

#include "agent.hpp"

float sigmoid(float x)
{
    return 1.0f / (1 + exp(-x));
}

float d_sigmoid(float x)
{
    return (x * (1 - x));
}



/**
 * Creates the tapology that will be used to configure agent.
 */
void Agent::create_topology()
{
    Logger::info("creating toplogy for agent " + _nid);
    _units_per_layer.clear();
    _units_per_layer.push_back(_input_nodes_sz);

    for (size_t i = 0; i < _layers_sz; i++)
    {
        // each hidden layer is the same size as input layer + 1 extra neuron for bias.
        _units_per_layer.push_back(_input_nodes_sz + 1);
    }
    _units_per_layer.push_back(_output_nodes_sz);
}

Matrix randn(size_t rows, size_t cols)
{
    Matrix m(rows, cols);

    std::random_device rd{};
    std::mt19937 gen{rd()};

    // init Gaussian distr. w/ N(mean=0, stdev=1/sqrt(numel))
    float n = float(m.size());
    float stdev{1 / sqrt(n)};
    std::normal_distribution<float> d{0, stdev};

    // fill each element w/ draw from distribution
    for (size_t r = 0; r < m.rows(); ++r)
    {
        for (int c = 0; c < m.cols(); ++c)
        {
            m(r, c) = d(gen);
        }
    }

    return m;
}

/********************************************************
 * setup method.
 *
 * The tapology variable used in the example is something like this
 * NeuralNetwork n({ 2, 3, 1 });
 *
 * Assuming that translates to 2 nodes in input, 3 nodes in
 * hidden layer,  and 1 node for output,  which should solve
 * a xor test.
 ********************************************************/
void Agent::setup(string nid, ConfigReader *config)
{
    Logger::info("configuring agent");
    _nid = nid;
    _initial_weight_max = config->nn_inital_weight(_nid);
    _success = config->nn_success(_nid);
    _learning_rate = config->nn_learning_rate(_nid);
    _momentum = config->nn_momentum(_nid);

    _input_nodes_sz = config->input_nodes(_nid);
    _output_nodes_sz = config->output_nodes(_nid);
    _layers_sz = config->hidden_layers(_nid);

    create_topology();

    for (size_t i = 0; i < _units_per_layer.size() - 1; ++i)
    {
        size_t in_channels{_units_per_layer[i]};
        size_t out_channels{_units_per_layer[i + 1]};

        // initialize to random Gaussian
        auto W = randn(out_channels, in_channels);
        _weight_matrices.push_back(W);

        auto b = randn(out_channels, 1);
        _bias_vectors.push_back(b);

        _activations.resize(_units_per_layer.size());
    }
}

// matmul
// apply_function
Matrix Agent::forward_propagate(Matrix &x)
{
    Logger::info("begin forward propagation");
    // assert(get<0>(x.shape) == units_per_layer[0] && get<1>(x.shape));

    _activations[0] = x;
    Matrix prev(x);
    for (int i = 0; i < _units_per_layer.size() - 1; ++i)
    {
        Matrix y = _weight_matrices[i] * prev;
        y = y + _bias_vectors[i];
        y.unaryExpr(&sigmoid);
        _activations[i + 1] = y;
        prev = y;
    }

    return prev;
}


/**
 * Delta is bias vector I think? 
 */
void Agent::backward_propagate(Matrix &target)
{
    Logger::info("Backpropagate errors to hidden layer(s)");

    // Matrix y = target;
    // Matrix y_hat = _activations.back();

    // // DEBUG CODE.
    // // END CODE

    // compute total error which is accum(target) - accum(output)
    // float error = (target.colwise().sum().sum() - _layers.back().colwise().sum().sum());

    // backprop the error from output to input and step the weights
    for (int i = _weight_matrices.size() - 1; i >= 0; --i)
    {
        // calculating errors for previous layer
        auto Wt = _weight_matrices[i];

        // Delta is mean to be a matrix but I can see if defined anywhere, nor do I
        // know how it is accessed in this context.
        // auto prev_errors = Wt * _delta;

        // // apply derivative of function evaluated at activations
        // // backprop for biases
        // auto d_outputs = _activations[i + 1].unaryExpr(d_sigmoid);
        // auto gradients = error * d_outputs;
        // gradients = gradients.multiply_scalar(_learning_rate);

        // // backprop for weights
        // auto a_trans = _activations[i];
        // auto weight_gradients = gradients * a_trans;

        // // adjust weights
        // _bias_vectors[i] = _bias_vectors[i] + gradients;
        // _weight_matrices[i] = _weight_matrices[i] + weight_gradients;
        // error = prev_errors;
    }
}