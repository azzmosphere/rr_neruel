#include "ActionFactory.hpp"




using namespace std;

ActionFactory::ActionFactory()
{

    Logger::info("initlising wiringPi");
    if (wiringSetup() < 0) {
        Logger::error("fatal error could not initialise wiring");
        throw "fatal error could not initialise wiring";
    }

    // TODO: initilise this Actions.
    Logger::info("initializing motorA/B");
    L298Motor* motorA = new L298Motor();
    motorA->setup();

    MoveForwardAction* actionMoveForward = new MoveForwardAction(motorA);
    _actions.insert({1, actionMoveForward});

    StopAction *actionStop = new StopAction(motorA);
    _actions.insert({2, actionStop});

}


void ActionFactory::performAction(int8_t _oid, float value)
{
    Action *action = _actions.at(_oid);
    Logger::info("performing action: " + action->name());
    action->executeAction(value);
}