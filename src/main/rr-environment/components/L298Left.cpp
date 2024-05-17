/************************************************************
 * Move Robot Left.
 ************************************************************/

#include "L298Left.hpp"

MoveLeftAction::MoveLeftAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void MoveLeftAction::executeAction(float value)
{
    Logger::info("executing left forward");
    _l298Motor->driveWheels(LOW, HIGH, HIGH, LOW, value, value);
}

string MoveForwardAction::name() 
{
    return "move left";
}