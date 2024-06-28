/************************************************************
 * Move Robot Righ.
 ************************************************************/

#include "components/L298Right.hpp"

MoveRighAction::MoveRighAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void MoveRighAction::executeAction(float value)
{
    Logger::info("executing left forward");
    _l298Motor->driveWheels(LOW, HIGH, HIGH, LOW, value, value);
}

string MoveRighAction::name() 
{
    return "move right";
}