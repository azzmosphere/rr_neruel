/************************
* Determine wiring.
*************************/

#include <stdlib.h>
#include <stdio.h>
#include "wiringiface.hpp"

#define GPIO_PIN12 12
#define GPIO_PIN13 13
#define GPIO_PIN17 17
#define GPIO_PIN23 23
#define GPIO_PIN24 24
#define GPIO_PIN27 27

const int IN1 = GPIO_PIN23;
const int IN2 = GPIO_PIN24;
const int ENA = GPIO_PIN12;

const int IN3 = GPIO_PIN27;
const int IN4 = GPIO_PIN17;
const int ENB = GPIO_PIN13;

void teardown() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    pwmWrite(ENA, 0);
    pwmWrite(ENB, 0);
}

void __attribute__ ((constructor)) setup()
{
   wiringPiSetupGpio();
}

int main()
{
    atexit(teardown);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, PWM_OUTPUT);

    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, PWM_OUTPUT);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // range is 0 to 1024
    pwmWrite(ENA, 500);
    pwmWrite(ENB, 500);

    delay(2000);
    pwmWrite(ENA, 1000);
    pwmWrite(ENB, 1000);

    delay(8000);
    return 0;
}