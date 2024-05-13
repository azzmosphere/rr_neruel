#include "L298Motor.hpp"

void L298Motor::setIn1(uint32_t in)
{
    _in1 = in;
}

void L298Motor::setIn2(uint32_t in)
{
    _in2 = in;
}

void L298Motor::setIn3(uint32_t in)
{
    _in3 = in;
}

void L298Motor::setIn4(uint32_t in)
{
    _in4 = in;
}

void L298Motor::setEnA(uint32_t in)
{
    _enA = in;
}


void L298Motor::setEnB(uint32_t in)
{
    _enB = in;
}

void L298Motor::driveWheels(uint32_t in1, uint32_t in2, uint32_t in3,  uint32_t in4, uint32_t ena, uint32_t enb)
{
    digitalWrite(_in1, in1);
    digitalWrite(_in2, in2);

    digitalWrite(_in3, in1);
    digitalWrite(_in4, in2);
    
    pwmWrite(_enA, ena);
    pwmWrite(_enB, ena);
}

void L298Motor::setup()
{

    setEnA(ENA);
    setEnB(ENB);

    setIn1(IN1);
    setIn2(IN2);
    setIn3(IN3);
    setIn4(IN4);

    // softPwmCreate(_enA, 0, 100);
    // softPwmCreate(_enB, 0, 100);

    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);

    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);

    pinMode(_enA, PWM_OUTPUT);
    pinMode(_enB, PWM_OUTPUT);

        // set the PWM mode to Mark Space
    pwmSetMode(PWM_MODE_BAL);
    pwmSetClock (3840);  // 19.2 Mhz divided by 3840 is 5 Khz.
    pwmSetRange (2500); 


}

void L298Motor::teardown()
{

}
