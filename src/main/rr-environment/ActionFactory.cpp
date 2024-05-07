#include "ActionFactory.hpp"

// TODO: this needs to go into a config file,  but for now
// purple wire
#define in1 4
#define in2 5
#define enA 6


using namespace std;

ActionFactory::ActionFactory()
{

    Logger::info("initlising wiringPi");
    wiringPiSetup();

    // TODO: initilise this Actions.
    Logger::info("initializing motor A");
    L298Motor* motorA = new L298Motor();

    motorA->setEn(enA);
    motorA->setIn1(in1);
    motorA->setIn2(in2);
    motorA->setup();

    SeedL298MoveForwardAction* actionMoveForward = new SeedL298MoveForwardAction(motorA);

    _actions.insert({1, actionMoveForward});

}


void ActionFactory::performAction(int8_t _oid, float value)
{
    Logger::info("performing action: " + _actions.at(_oid)->name());
    _actions.at(_oid)->executeAction(value);
}