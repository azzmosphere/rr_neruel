#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include "attribute.hpp"

class Event {
    public:
        string to_string();
        void deserialize(string in);

    private:
        uint8_t           _opcode;   // operation code 
        vector<Attribute> _actions;  // actions
        vector<Attribute> _observations; // observations
};

#endif