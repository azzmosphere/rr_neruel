/************************************************************
 * Move Robot Left.
 ************************************************************/

#include "components/L298Left.hpp"

MoveLeftAction::MoveLeftAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void MoveLeftAction::executeAction(float value)
{
    Logger::info("executing left forward");
    _l298Motor->driveWheels(HIGH, LOW, LOW, HIGH, value, value);
}

string MoveLeftAction::name() 
{
    return "move left";
}