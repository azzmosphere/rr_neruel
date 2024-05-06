/***
 * interact with hardware do stuff!
*/

#include "RrController.hpp"


// TODO: this needs to go into a config file,  but for now
// purple wire
#define in1 4
#define in2 5
#define enA 6

//SeeedL298 l298;

RrController::RrController() {
    Logger::info("initlising wiringPi");
    wiringPiSetup();

    // TODO: initilise this Actions.
    Logger::info("initializing motor A");
    L298Motor motorA;

    motorA.setEn(enA);
    motorA.setIn1(in1);
    motorA.setIn2(in2);
    motorA.setup();

}

Event RrController::executeRequest(Event event)
{
    
    return event;
}
