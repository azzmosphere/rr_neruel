#ifndef L298MOTOR
#define L298MOTOR

#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

#include "Logger.hpp"


const uint32_t IN1 16; // pysical pin 16 GPIO23
const uint32_t IN2 18; // pysical pin 18  GPIO24
const uint32_t ENA 25; // pysical pin 32  GPIO12 

const uint32_t IN3 29; // 
const uint32_t IN4 31;
const uint32_t ENB 33;



class L298Motor {
    private:
        uint32_t _in1;
        uint32_t _in2;
        uint32_t _en;

    public:
        void setIn1(uint32_t in);

        void setIn2(uint32_t in);

        void setEn(uint32_t in);

        void setup();

        void teardown();

        void driveWheels(uint32_t in1, uint32_t in2, uint32_t in3,  uint32_t in4, uint32_t ena, uint32_t enb);
};

#endif