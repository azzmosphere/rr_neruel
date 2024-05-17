/*********************************************
 * Base class for L298 Actions
*********************************************/

#ifndef L298_HPP
#define L298_HPP

#include "../Action.hpp"
#include "wiringiface.hpp"
#include "L298Motor.hpp"
#include "Logger.hpp"

class L298 : public Action {
    protected:
        L298Motor* _l298Motor;
};

#endif