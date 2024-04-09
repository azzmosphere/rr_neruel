#ifndef TRAININGSET_HPP
#define TRAININGSET_HPP


#include "nlohmann/json.hpp"
#include "Logger.hpp"
#include <fstream>
#include "FileReader.hpp"

class TrainingSet : FileReader {

    private:
        

    public:
        std::vector<std::vector<float> > _target;
        std::vector<std::vector<float> > _ingress;

        void deserialize(std::string file);
};
#endif