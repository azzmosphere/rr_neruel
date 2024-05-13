#include "L298Stop.hpp"

StopAction::StopAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void StopAction::executeAction(float value)
{
    Logger::info("executing stop");
    _l298Motor->driveWheels(LOW, LOW, LOW, LOW, 0, 0);
    _l298Motor->teardown();
}

string StopAction::name() 
{
    return "stop motor";
}
