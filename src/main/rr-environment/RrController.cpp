/***
 * interact with hardware do stuff!
*/

#include "RrController.hpp"


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
            try {
                _actionFactory.performAction(a.getOid(), a.getValue());
            } 
            catch( const exception& e)  
            { 
                Logger::error("could complete action " + a.getName());
            }
        }
        
    }
    return event;
}
