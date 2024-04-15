#include "nn.hpp"

#define TEST_INITAL_WEIGHT 1.
#define TEST_SUCCESS       2.
#define TEST_LEARNING_RATE 3.
#define TEST_MOMENTUM      4.
#define INPUT_NODE_SZ      1
#define NN_NID "nid01"

class MockConfigReader : public ConfigReader {
    // set the defaults we want here.
    public:
    MockConfigReader() {
        _nn_success       = TEST_SUCCESS;
        _nn_inital_weight = TEST_INITAL_WEIGHT;
        _nn_learning_rate = TEST_LEARNING_RATE;
        _nn_momentum      = TEST_MOMENTUM;
        _input_nodes      = INPUT_NODE_SZ;
        _hidden_layers    = 1;
        _hidden_nodes     = 2;
        _output_nodes     = 1;
    }
};

class TestNN : public NN {
    public:
    float test_initial_weight() {
        return _initial_weight_max;
    }

    float test_success() {
        return _success;
    }

    float test_learning_rate() {
        return _learning_rate;
    }
};

MockConfigReader config_reader;
TestNN network;

bool test_setup() {
    network.setup(NN_NID, config_reader);

    return (
        network.test_success() == TEST_SUCCESS &&
        network.test_initial_weight() == TEST_INITAL_WEIGHT &&
        network.test_learning_rate() == TEST_LEARNING_RATE
    );
}

//ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i];
bool test_update_weights() {
    // B O D M A S
    // ChangeHiddenWeights[InputNodes][i]  = 
    // LearningRate                        = 3
    // HiddenDelta                         = 1
    // Momentum                            = 4
    // ChangeHiddenWeights                 = 0
    // 3 * 1 + 4 * 0 = 3 + 0 = 3

    //network.update_inner_hidden_weights();
    return true;
}

int main() 
{
    

    if (!test_setup()) return 1;
    return 0;
}

