#ifndef SEEEDL298STOP_HPP
#define SEEEDL298STOP_HPP

#include "L298.hpp"

class StopAction : public L298
{
    public:
        StopAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
