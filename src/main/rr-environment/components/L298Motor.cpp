#include "L298Motor.hpp"

void L298Motor::setIn1(uint32_t in)
{
    _in1 = in;
}

void L298Motor::setIn2(uint32_t in)
{
    _in2 = in;
}

void L298Motor::setEn(uint32_t in)
{
    _en = in;
}

void L298Motor::setup()
{
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_en, OUTPUT);
}
