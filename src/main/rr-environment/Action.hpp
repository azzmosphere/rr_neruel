#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>

using namespace std;

class Action 
{
    public:
        virtual void executeAction(float value) {}

        virtual string name() 
        {
            return "";
        }
};

#endif