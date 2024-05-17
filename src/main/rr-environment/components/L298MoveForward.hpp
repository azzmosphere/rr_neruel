#ifndef SEEEDL298MOVEFORWARD_HPP
#define SEEEDL298MOVEFORWARD_HPP

#include "L298.hpp"

class MoveForwardAction : public L298
{
    public:
        MoveForwardAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
