#ifndef NETWORK_HPP
#define NETWORK_HPP


#include <stdlib.h>
#include "Logger.hpp"

class Network {
    public:
        void initalize(
            const size_t nid,
            const size_t nhidden, 
            const size_t ninodes,
            const size_t nhnodes, 
            const size_t nonodes);

    private:
            size_t _nhidden;
            size_t _ninodes;
            size_t _nhnodes; 
            size_t _nonodes;  
            size_t _nid;   
};

#endif