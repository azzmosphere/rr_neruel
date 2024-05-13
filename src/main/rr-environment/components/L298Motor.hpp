#ifndef L298MOTOR
#define L298MOTOR

#include <stdint.h>
#include "wiringiface.hpp"
#include "Logger.hpp"


const uint32_t IN1 = 24; // orange
const uint32_t IN2 = 23; // 
const uint32_t ENA = 12; // pysical pin 32  GPIO12 

const uint32_t IN3 = 5; // 
const uint32_t IN4 = 6;
const uint32_t ENB = 13;



class L298Motor {
    private:
        uint32_t _in1;
        uint32_t _in2;

        uint32_t _in3;
        uint32_t _in4;

        uint32_t _enA;
        uint32_t _enB;

    public:
        void setIn1(uint32_t in);

        void setIn2(uint32_t in);

        void setIn3(uint32_t in);

        void setIn4(uint32_t in);

        void setEnA(uint32_t in);

        void setEnB(uint32_t in);

        void setup();

        void teardown();

        void driveWheels(uint32_t in1, uint32_t in2, uint32_t in3,  uint32_t in4, uint32_t ena, uint32_t enb);
};

#endif