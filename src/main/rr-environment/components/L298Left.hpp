#ifndef L298LEFT_HPP
#define L298LEFT_HPP

#include "../Action.hpp"
#include "wiringiface.hpp"
#include "L298Motor.hpp"
#include "Logger.hpp"

class MoveLeftAction : public Action
{
    private:
        L298Motor* _l298Motor;

    public:
        MoveLeftAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
