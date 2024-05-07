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

void L298Motor::driveWheels(uint32_t in1, uint32_t in2, uint32_t in3,  uint32_t in4, uint32_t ena, uint32_t enb)
{
    digitalWrite(_in1, in1);
    digitalWrite(_in2, in2);
    
    pwmWrite(_en, ena);
}

void L298Motor::setup()
{
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_en, PWM_OUTPUT);
}
