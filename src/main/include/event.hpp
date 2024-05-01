#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include "attribute.hpp"

class Event {
    public:
        void setOpCode(uint8_t opcode)
        {
            _opcode = opcode;
        }

        void pushAction(Attribute event)
        {   
            _actions.push_back(event);
        }

        void pushObservations(Attribute event)
        {   
            _observations.push_back(event);
        }

        void pushRewards(Attribute event)
        {   
            _rewards.push_back(event);
        }

        uint8_t getOpCode() 
        {
            return _opcode;
        }


    private:
        uint8_t           _opcode;   // operation code 
        vector<Attribute> _actions;  // actions
        vector<Attribute> _observations; // observations
        vector<Attribute> _rewards;  // reward(s) allocated for this state.
};

#endif