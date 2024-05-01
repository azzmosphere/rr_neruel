/*****************************************************
 * accepts and sends requests requests from inbound 
 * port.
 *****************************************************/

#ifndef IPSERVER_HPP
#define IPSERVER_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <limits>
#include <string>
#include "Logger.hpp"
#include "event.hpp"

#define IP_BUFFSZ  8192
#define IP_BACKLOG_CONN 5


class IpServer {
    private:
        char _buffer[IP_BUFFSZ] = {0};
        int _server_socket;
        int _client_socket;

    public:
        Event receive();
        void send(Event msg);

        IpServer(u_int16_t in_port);
        ~IpServer();
};

#endif
