#ifndef L298MOTOR
#define L298MOTOR

#include <wiringPi.h>
#include <stdint.h>

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

        void driveWheels(uint32_t in1, uint32_t in2, uint32_t in3,  uint32_t in4, uint32_t ena, uint32_t enb);
};

#endif