#ifndef L298RIGHT_HPP
#define L298RIGHT_HPP

#include "L298.hpp"

class MoveRighAction : public L298
{
    public:
        MoveRighAction(L298Motor* l298Motor);

        void executeAction(float value) override;

        string name() override;
};

#endif
