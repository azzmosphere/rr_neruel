#ifndef L298LEFT_HPP
#define L298LEFT_HPP

#include "L298.hpp"

class MoveLeftAction : public L298
{
    public:
        MoveLeftAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
