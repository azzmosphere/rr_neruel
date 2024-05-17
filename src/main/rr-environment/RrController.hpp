/**
 * NOTE this is not a rest controller!
 * 
 * It does not use a URL,  the return value will always be the current environment state, as percieved by the 
 * observers in full.
 * 
 * input string is a JSON list of actions to perform.
 */

#ifndef RR_CONTROLLER_HPP
#define RR_CONTROLLER_HPP

#include <wiringPi.h>
#include <vector>

#include "event.hpp"
#include "Logger.hpp"
#include "components/L298Motor.hpp"
#include "ActionFactory.hpp"

using namespace std;

class RrController {
    private:
        ActionFactory _actionFactory;

    public: 
        RrController();
        Event executeRequest(Event request);
};

#endif