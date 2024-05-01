/************************************************************
 * 
 *************************************************************/

#include "ipserver.hpp"

IpServer::IpServer(uint16_t in_port) 
{
    _server_socket =  socket(AF_INET, SOCK_STREAM, PF_UNSPEC);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(in_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(_server_socket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0) 
    {
        throw "unable to create binding port, errno: " + to_string(errno);
    }

    if (listen(_server_socket, IP_BACKLOG_CONN) != 0) 
    {
         throw "unable to create binding port, errno: " + to_string(errno);
    }
}


 IpServer::~IpServer()
 {
    Logger::info("closing server connection");
    close(_server_socket);
 }

 void  IpServer::send(Event msg)
 {
    string m = "{server response}";
    ::send(_client_socket, m.c_str(), m.size(), 0);
    ::close(_client_socket);
 }

/**
 * get data of the socket and convert it to an event. 
 */
 Event  IpServer::receive()
 {
    _client_socket = accept(_server_socket, nullptr, nullptr);
    ::recv(_client_socket, _buffer, sizeof(_buffer), 0);
    return Event();
 }