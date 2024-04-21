#include "config.hpp"
#include "agent.hpp"

// Hard code some values,
/*
  - id: "network0"
    success:  0.0004
    inital_weight: 0.5
    learning_rate: 0.3
    momentum: 0.9
*/
class MockConfig : public ConfigReader
{
public:
    float nn_inital_weight(const string nid)
    {
        return 0.5;
    }

    float nn_success(const string nid)
    {
        return 0.0004;
    };

    float nn_learning_rate(const string nid)
    {
        return 0.3;
    };

    float nn_momentum(const string nid)
    {
        return 0.9;
    };

    // Need to work out network topology

    unsigned int hidden_layers(const string nid)
    {
        return 1; // this may change,  but lets keep it same/same for now.
    };

    unsigned int input_nodes(const string nid)
    {
        return 7;
    };

    unsigned int output_nodes(const string nid)
    {
        return 4;
    };
};

// Object that is getting tested.
class ObjectUnderTest : public Agent
{
public:
    vector<size_t> getTopology()
    {
        return _units_per_layer;
    }
};

void test_create_topology() 
{
    ObjectUnderTest agent1;
    MockConfig config;

    agent1.setup("nid0", &config);

    Logger::info("topology size: " + to_string(agent1.getTopology().size()));
    assert(agent1.getTopology().size() == 3);

    Logger::info("input layer num of neurons:" + to_string(agent1.getTopology().at(0)));
    assert(agent1.getTopology().at(0) == 7);

    Logger::info("hidden layer num of neurons:" + to_string(agent1.getTopology().at(1)));
    assert(agent1.getTopology().at(1) == 8);

    Logger::info("hidden layer num of neurons:" + to_string(agent1.getTopology().at(2)));
    assert(agent1.getTopology().at(2) == 4);
}

int main()
{

    test_create_topology();
    return 0;
}