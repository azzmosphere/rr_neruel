/****************************************************************************
 * Communicate all responses from observers (current state).  Accept action(s)
 * as input, and interact with hardware to peform tasks.
 * 
 * REFERECNE: https://www.geeksforgeeks.org/socket-programming-in-cpp/
 ****************************************************************************/

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Logger.hpp"


// These will be turned into configuration options
#define BACKLOG_CONN 5
#define IN_PORT 8080

using namespace std; 
int main() 
{
    Logger::info("creating socket");
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); 

    // specifying the address 
    Logger::info("configuring socket");
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(IN_PORT); 
    serverAddress.sin_addr.s_addr = INADDR_ANY; 


      
    // binding socket. 
    bind(serverSocket, (struct sockaddr*)&serverAddress, 
         sizeof(serverAddress)); 


    // listening to the assigned socket 
    listen(serverSocket, BACKLOG_CONN); 


    // accepting connection request 
    int clientSocket 
        = accept(serverSocket, nullptr, nullptr); 

     // recieving data 
    char buffer[1024] = { 0 }; 
    recv(clientSocket, buffer, sizeof(buffer), 0); 
    cout << "Message from client: " << buffer 
              << endl; 
  
    // closing the socket. 
    close(serverSocket); 
  
    return 0; 
}