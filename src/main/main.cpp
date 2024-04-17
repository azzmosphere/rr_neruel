#include "nn.hpp"
#include <getopt.h>


const float NN_INITIAL_WEIGHT = 0.5;
NN network;
ConfigReader config;


// Perform any network(s) configuration, inject config file,  
// add MPIO
void setup() 
{
    config.load_file("/Users/newuser/projects/rr_neruel/resources/etc/config.yaml");
    network.setup("nid0", config);
    network.initialize_hidden();
    network.initialize_output();
}

// Need to get a file format going for training sets.  Training should happen, here for each network.
void train(const string tset_file) 
{
    TrainingSet tset;
    tset.deserialize(tset_file);
    network.train(tset);
}

void process_args(int argc, char** argv) {
    const char* const short_opts = "t:c:";
    const option long_opts[] = {
        {"config", required_argument, nullptr, 'c'},
        {"tdir",   optional_argument, nullptr, 't'},
        {"help",   no_argument,       nullptr, 'h'}
    };

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
                //string config_file = string(optarg);
                Logger::info("config set: " + string(optarg));
                //config.load_file(string(optarg));
                break;

            // training set.
            case 't':
                //string tdata = string(optarg);
                Logger::info("trainging set: " + string(optarg));
                // training_set = string(optarg);
                break;

            default:
                cout << "print this help screen" << endl;
                break;
        }
     }
}

int main(int argc, char** argv) 
{
    setup();

    train("/Users/newuser/projects/rr_neruel/resources/training/training-set.0.json");

    // Perform some predictions to finish off the testing.
    vector<float> ingress = {1, 1, 1, 0, 0, 0, 0};
    network.predict(ingress);

    for (int i = 0; i < network._output_nodes_sz; i++) {
        Logger::info("col " + to_string(i) + ": " + to_string(network._output._nodes.at(i)));
    }

    return 0;
}