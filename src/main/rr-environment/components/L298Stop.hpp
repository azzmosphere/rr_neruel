#ifndef SEEEDL298STOP_HPP
#define SEEEDL298STOP_HPP

#include "../Action.hpp"
#include "L298Motor.hpp"
#include "Logger.hpp"

class StopAction : public Action
{
    private:
        L298Motor* _l298Motor;

    public:
        StopAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
