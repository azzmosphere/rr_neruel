#include "L298Motor.hpp"

const int IN1 = GPIO_PIN23;
const int IN2 = GPIO_PIN24;
const int ENA = PWM0;

const int IN3 = GPIO_PIN27;
const int IN4 = GPIO_PIN17;
const int ENB = PWM1;

void L298Motor::driveWheels(int in1, int in2, int in3,  int in4, int ena, int enb)
{
    digitalWrite(IN1, in1);
    digitalWrite(IN2, in2);

    digitalWrite(IN3, in3);
    digitalWrite(IN4, in4);

    // range is 0 to 1024

    pwmWrite(ENA, ena);
    pwmWrite(ENB, enb);
}

void L298Motor::setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, PWM_OUTPUT);

    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, PWM_OUTPUT);
}

void L298Motor::teardown()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    pwmWrite(ENA, 0);
    pwmWrite(ENB, 0);
}
