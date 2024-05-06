#ifndef SEEEDL298MOVEFORWARD_HPP
#define SEEEDL298MOVEFORWARD_HPP

#include "SeeedL298.hpp"
#include "../Action.hpp"

class SeedL298MoveForwardAction : public Action
{
    private:
        SeeedL298 seeedL298;

    public:
        void executeAction(float value)
        {
        }
};

#endif
