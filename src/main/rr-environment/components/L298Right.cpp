/************************************************************
 * Move Robot Righ.
 ************************************************************/

#include "L298Right.hpp"

MoveRighAction::MoveRighAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void MoveRighAction::executeAction(float value)
{
    Logger::info("executing left forward");
    _l298Motor->driveWheels(HIGH, LOW, LOW, HIGH, value, value);
}

string MoveRighAction::name() 
{
    return "move right";
}