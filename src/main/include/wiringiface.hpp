/********************************************************************
 * common headers, and macros to explain wiring setup.
 ********************************************************************/



#ifndef WIRINGIFACE_HPP
#define WIRINGIFACE_HPP

#include <wiringPi.h>
// #include <softPwm.h>

#define WPI_GPIO 0
#define WPI_PI   1
#define WPI_PYS  2

// define the wiring setup to use. 
#define WIRINGSETUP WPI_GPIO

#if WIRINGSETUP == WPI_GPIO
#define wiringSetup() wiringPiSetupGpio()

// WiringPI mnumbering
#elif WIRINGSETUP == WPI_PI
#define wiringSetup() wiringPiSetup()

// Pysical PIN location numbering
#elif WIRINGSETUP == WPI_PYS
#define wiringSetup() wiringPiSetupPhys()
#endif

// General purpose pins
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN17 17
#define GPIO_PIN22 22
#define GPIO_PIN23 23
#define GPIO_PIN24 24
#define GPIO_PIN25 25
#define GPIO_PIN26 26
#define GPIO_PIN27 27


// PWM Pins
#define GPIO_PIN12 12
#define GPIO_PIN13 13
#define PWM0 GPIO_PIN12
#define PWM1 GPIO_PIN13

#endif