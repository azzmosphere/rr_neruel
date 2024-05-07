/***
 * interact with hardware do stuff!
*/

#include "RrController.hpp"


#define DELAY_MS 100

RrController::RrController() {}

// create a delay configurable before actioning the requests.
Event RrController::executeRequest(Event event)
{
    
    // execute actions
    if (event.getOpCode() & OP_ACTIONS) 
    {
        vector<Attribute> actions =  event.getActions();
        for (Attribute& a : actions)
        {
            _actionFactory.performAction(a.getOid(), a.getValue());
        }
        
    }
    delayMicroseconds(DELAY_MS);
    return event;
}
