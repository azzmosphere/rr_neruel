#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <vector>
#include "attribute.hpp"

class Actions {
    public:
        string to_string();
        void deserialize(string in);

    private:
        vector<Attribute> _attributes;
};

#endif