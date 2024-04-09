#include "main.hpp"

Network network;
TrainingSet tset;
string tdata;
string config_file;

void process_args(int argc, char** argv);
void setup();

int main(int argc, char** argv) {
    process_args(argc, argv);
    setup();
    return EXIT_SUCCESS;
}


void process_args(int argc, char** argv) {
    const char* const short_opts = "t:c:";
    const option long_opts[] = {
        {"tdata", required_argument, nullptr, 't'},
        {"config", optional_argument, nullptr, 'c'}
    };

     while (true)
     {
         const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt) 
        {
            // training set.
            case 't':
                tdata = string(optarg);
                Logger::info("trainging set: " + tdata);
                break;
            // config file
            case 'c':
                config_file = string(optarg);
                Logger::info("config set: " + config_file);
                break;

        }
     }
}

void setup() {
    /***************************************
    // TODO: This needs to go into a configuration filer somewhere, once JSON is working.
    // 1 - Hidden Layers
    // 7 - Input Nodes
    // 8 - Nodes in each hidden layer
    // 4 - Output nodes.
    *****************************************/
    const size_t hl = 2;
    const size_t in = 7;
    const size_t ln = 8;
    const size_t on = 4;
    const size_t nid = 0;

    ConfigReader config_reader;
    config_reader.load_file(config_file);

    network.initalize(nid, hl, in, ln, on);
    
    // start deserializing data
    tset.deserialize(tdata);

    // train network.
    network.train(tset);
}