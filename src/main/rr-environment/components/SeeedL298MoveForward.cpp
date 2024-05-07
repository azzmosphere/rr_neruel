/************************************************************************************
 * Instructs the engine to move forward.
 ************************************************************************************/

#include "SeeedL298MoveForward.hpp"

using namespace std;

SeedL298MoveForwardAction::SeedL298MoveForwardAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void SeedL298MoveForwardAction::executeAction(float value)
{
    Logger::info("executing move forward");
    _l298Motor->driveWheels(HIGH, HIGH, HIGH, HIGH, value, value);
}

string SeedL298MoveForwardAction::name() 
{
    return "move forward";
}