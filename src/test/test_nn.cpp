#include "nn.hpp"

#define TEST_INITAL_WEIGHT 0.5
#define TEST_SUCCESS       1.0
#define TEST_LEARNING_RATE 0.5
#define NN_NID "nid01"

class MockConfigReader : public ConfigReader {
    // set the defaults we want here.
    public:
    MockConfigReader() {
        _nn_success       = TEST_SUCCESS;
        _nn_inital_weight = TEST_INITAL_WEIGHT;
        _nn_learning_rate = TEST_LEARNING_RATE;
        _nn_momentum      = 0.9;
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

int main() 
{
    

    if (!test_setup()) return 1;
    return 0;
}

