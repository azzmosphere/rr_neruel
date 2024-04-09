#include "TrainingSet.hpp"

using json = nlohmann::json;


//
// Attempt to read training set andmatching target output from inpu file
// and create a vector which uses them.
void TrainingSet::deserialize(std::string file) {
    Logger::info("Deserializing: " + file);
    std::ifstream f(trim(file));
    json data = json::parse(f);

    for (auto it : data) {
        std::vector<float> ts;
        for (auto i : it["ingress"]) {
            ts.push_back(float(i));
        }
        _ingress.push_back(ts);

        std::vector<float> tg;
        for (auto i : it["target"]) {
            tg.push_back(float(i));
        }
        _target.push_back(tg);
    }
    Logger::info("Deserialized " + file);
    f.close();
}