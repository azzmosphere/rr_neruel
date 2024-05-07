#include "SeeedL298MoveForward.hpp"

using namespace std;

SeedL298MoveForwardAction::SeedL298MoveForwardAction(L298Motor* l298Motor)
{
    _l298Motor = l298Motor;
}

void SeedL298MoveForwardAction::executeAction(float value)
{

}

string SeedL298MoveForwardAction::name() 
{
    return "move forward";
}