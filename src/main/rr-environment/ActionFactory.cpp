#include "ActionFactory.hpp"




using namespace std;

ActionFactory::ActionFactory()
{

    Logger::info("initlising wiringPi");
    if (wiringSetup() < 0) {
        return;
    }

    // TODO: initilise this Actions.
    Logger::info("initializing motor A");
    L298Motor* motorA = new L298Motor();


    motorA->setup();

    SeedL298MoveForwardAction* actionMoveForward = new SeedL298MoveForwardAction(motorA);
    _actions.insert({1, actionMoveForward});

    SeedL298StopAction *actionStop = new SeedL298StopAction(motorA);
    _actions.insert({2, actionStop});

}


void ActionFactory::performAction(int8_t _oid, float value)
{
    Logger::info("performing action: " + _actions.at(_oid)->name());
    _actions.at(_oid)->executeAction(value);
}