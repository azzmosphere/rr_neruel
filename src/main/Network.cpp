#include "Network.hpp"


void Network::initalize(
            const size_t nid,
            const size_t nhidden, 
            const size_t ninodes,
            const size_t nhnodes, 
            const size_t nonodes) 
{
    Logger::info("initializing network:" + to_string(nid) + " :"
        + std::string(" nhidden:") + to_string(nhidden)
        + std::string(" ninodes:") + to_string(ninodes)
        + std::string(" nhnodes:") + to_string(nhnodes)
        + std::string(" nonodes:") + to_string(nonodes)
    );
    _nhidden = nhidden;
    _ninodes = ninodes;
    _nhnodes = nhnodes;
    _nonodes = nonodes;
    _nid     = nid;

    Logger::info("network initalised");
}