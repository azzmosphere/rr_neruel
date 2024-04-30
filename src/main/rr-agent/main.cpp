// #include "nn.hpp"
#include "configyaml.hpp"
#include "TrainingSet.hpp"
#include <getopt.h>

const float NN_INITIAL_WEIGHT = 0.5;
// NN network;
ConfigYamlReader config;
string training_set;

// Perform any network(s) configuration, inject config file,
// add MPIO
void setup()
{
    // network.setup("nid0", config);
    // network.initialize_hidden();
    // network.initialize_output();
}

// Need to get a file format going for training sets.  Training should happen, here for each network.
bool train(const string tset_file)
{
    TrainingSet tset;
    tset.deserialize(tset_file);
    // return network.train(tset);
    return true;
}

void process_args(int argc, char **argv)
{
    const char *const short_opts = "t:c:";
    const option long_opts[] = {
        {"config", required_argument, nullptr, 'c'},
        {"tdir", optional_argument, nullptr, 't'},
        {"help", no_argument, nullptr, 'h'}};

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        // Help is first option so that loop is automatically broken
        case 'h':
            cout << "print this help screen" << endl;
            break;

        // config file
        case 'c':
            // string config_file = string(optarg);
            Logger::info("config set: " + string(optarg));
            config.load_file(string(optarg));
            break;

        // training set.
        case 't':
            // string tdata = string(optarg);
            Logger::info("trainging set: " + string(optarg));
            training_set = string(optarg);
            break;

        default:
            cout << "print this help screen" << endl;
            break;
        }
    }
}

int main(int argc, char **argv)
{
    process_args(argc, argv);
    setup();

    if (train(training_set))
    {

        // Perform some predictions to finish off the testing.
        vector<float> ingress = {1, 1, 1, 0, 0, 0, 0};
        // network.predict(ingress);

        // for (int i = 0; i < network._output_nodes_sz; i++)
        // {
        //     Logger::info("col " + to_string(i) + ": " + to_string(network._output._nodes.at(i)));
        // }
    }
    else
    {
        Logger::info("could not train model");
    }

    return 0;
}