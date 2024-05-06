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

#include "event.hpp"
#include "Logger.hpp"
#include "components/L298Motor.hpp"

class RrController {
    public: 
        RrController();
        Event executeRequest(Event request);
};

#endif