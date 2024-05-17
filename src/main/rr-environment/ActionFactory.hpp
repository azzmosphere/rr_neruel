/***********************************
 * Given a specifc action OID
 * do something.
 **********************************/

#ifndef ACTIONFACTORY_HPP
#define ACTIONFACTORY_HPP

#include <cstdint>
#include <map>

#include "Action.hpp"
#include "Logger.hpp"
#include "components/L298Motor.hpp"
#include "components/L298MoveForward.hpp"
#include "components/L298Stop.hpp"
#include "wiringiface.hpp"

using namespace std;
class ActionFactory {
    private:
        map<int8_t, Action*> _actions;

    public:
        ActionFactory();
        void performAction(int8_t _oid, float value);
};

#endif