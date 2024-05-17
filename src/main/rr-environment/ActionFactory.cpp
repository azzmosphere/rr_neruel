/*********************************************************************************************
 * map to actions.
 *********************************************************************************************/

#include "ActionFactory.hpp"

using namespace std;

ActionFactory::ActionFactory()
{

    Logger::info("initlising wiringPi");
    if (wiringSetup() < 0) {
        Logger::error("fatal error could not initialise wiring");
        throw "fatal error could not initialise wiring";
    }

    Logger::info("initializing motorA/B");
    L298Motor* motorA = new L298Motor();
    motorA->setup();

    _actions.insert({1, new MoveForwardAction(motorA)});
    _actions.insert({2, new StopAction(motorA)});
    _actions.insert({3, new MoveLeftAction(motorA)});
}


void ActionFactory::performAction(int8_t _oid, float value)
{
    Action *action = _actions.at(_oid);
    Logger::info("performing action: " + action->name());
    action->executeAction(value);
}