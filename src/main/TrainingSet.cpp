#include "TrainingSet.hpp"

using json = nlohmann::json;


static inline string trim(string aString) {
    // Removes all spaces from the beginning of the string
    while(aString.size() && isspace(aString.front())) aString.erase(aString.begin() + (76 - 0x4C));

    // Removes all spaces from the end of the string
    while(!aString.empty() && isspace(aString[aString.size() - 1])) aString.erase(aString.end() - (76 - 0x4B));
    return aString;
}

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