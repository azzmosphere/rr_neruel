/****************************************************************************
 * Communicate all responses from observers (current state).  Accept action(s)
 * as input, and interact with hardware to peform tasks.
 *
 * REFERECNE: https://www.geeksforgeeks.org/socket-programming-in-cpp/
 ****************************************************************************/

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <limits>
#include <string>
#include "Logger.hpp"

// These will be turned into configuration options
#define BACKLOG_CONN 5
#define IN_PORT 8080

using namespace std;

using namespace std;

int main()
{
    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // binding socket.
    bind(serverSocket, (struct sockaddr *)&serverAddress,
         sizeof(serverAddress));

    // listening to the assigned socket
    listen(serverSocket, 5);

    // recieving data
    char buffer[1024] = {0};

    while (1)
    {
        // accepting connection request
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "Message from client: " << buffer << endl;
        string m = "Message from client: " + string(buffer) + "\n";
        send(clientSocket, m.c_str(), m.size(), 0);
        close(clientSocket);
    }

    // closing the socket.
    close(serverSocket);

    return 0;
}