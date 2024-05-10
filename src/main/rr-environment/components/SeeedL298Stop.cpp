#include "SeeedL298Stop.hpp"

SeedL298StopAction::SeedL298StopAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void SeedL298StopAction::executeAction(float value)
{
    Logger::info("executing stop");
    _l298Motor->driveWheels(LOW, LOW, LOW, LOW, 0, 0);
    _l298Motor->teardown();
}

string SeedL298StopAction::name() 
{
    return "stop motor";
}
