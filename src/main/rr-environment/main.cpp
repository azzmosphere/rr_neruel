/****************************************************************************
 * Communicate all responses from observers (current state).  Accept action(s)
 * as input, and interact with hardware to peform tasks.
 *
 * REFERECNE: https://www.geeksforgeeks.org/socket-programming-in-cpp/
 ****************************************************************************/

#include "Logger.hpp"

#include "ipserver.hpp"
#include "RrController.hpp"

#define IN_PORT 8080

static IpServer *ipserver;

void _exit()
{
    Logger::info("closing connection");
    ipserver->~IpServer();
}

void _sig2(int sig)
{
    Logger::info("forced exit");
    exit(sig);
}

using namespace std;
int main()
{

    Logger::info("starting environmental service");
    IpServer server(IN_PORT);
    RrController controller;

    Logger::info("creating exit functions");
    ipserver = &server;
    atexit(_exit);
    signal(SIGINT, _sig2);

    while (true)
    {
        try
        {
            Event event = server.receive();
            server.send(controller.executeRequest(event));
        }
        catch (exception ex)
        {
            Logger::error("error occurred in request " + string(ex.what()));
        }
    }
    return EXIT_SUCCESS;
}
