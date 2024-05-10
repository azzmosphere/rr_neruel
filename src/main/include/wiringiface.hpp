/********************************************************************
 * common headers, and macros to explain wiring setup.
 ********************************************************************/



#ifndef WIRINGIFACE_HPP
#define WIRINGIFACE_HPP

#define WPI_GPIO 0
#define WPI_PI   1
#define WPI_PYS  2

// define the wiring setup to use. 
#define WIRINGSETUP WPI_PYS

#if WIRINGSETUP == WPI_GPIO
#define wiringSetup() wiringPiSetupGpio()

// WiringPI mnumbering
#elif WIRINGSETUP == WPI_PI
#define wiringSetup() wiringPiSetup()

// Pysical PIN location numbering
#elif WIRINGSETUP == WPI_PYS
#define wiringSetup() wiringPiSetupPhys()
#endif


#endif