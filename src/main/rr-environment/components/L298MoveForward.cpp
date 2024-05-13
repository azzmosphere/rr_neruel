/************************************************************************************
 * Instructs the engine to move forward.
 ************************************************************************************/

#include "L298MoveForward.hpp"

using namespace std;

MoveForwardAction::MoveForwardAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void MoveForwardAction::executeAction(float value)
{
    Logger::info("executing move forward");
    _l298Motor->driveWheels(HIGH, HIGH, HIGH, HIGH, value, value);
}

string MoveForwardAction::name() 
{
    return "move forward";
}