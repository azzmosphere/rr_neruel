#ifndef SEEEDL298MOVEFORWARD_HPP
#define SEEEDL298MOVEFORWARD_HPP

#include "../Action.hpp"
#include "L298Motor.hpp"
#include "Logger.hpp"

class SeedL298MoveForwardAction : public Action
{
    private:
        L298Motor* _l298Motor;

    public:
        SeedL298MoveForwardAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
