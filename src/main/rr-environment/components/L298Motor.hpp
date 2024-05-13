#ifndef L298MOTOR
#define L298MOTOR

#include <stdint.h>
#include "ComponentsCommon.hpp"
#include "Logger.hpp"

#define MAX_PWM_VAL 1024

class L298Motor {
    public:
        void setup();

        void teardown();

        void driveWheels(int in1, int in2, int in3,  int in4, int ena, int enb);
};

#endif