#include "components/L298Stop.hpp"

StopAction::StopAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void StopAction::executeAction(float value)
{
    Logger::info("executing stop");
    _l298Motor->teardown();
}

string StopAction::name() 
{
    return "stop motor";
}
