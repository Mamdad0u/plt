#include <server/Server.h>
#include "Server.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;
using namespace server;

#define SOCKET_ERROR -1

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct addrinfo ADDRINFO;
struct addrinfo * result;

SOCKADDR_IN server_sockaddr_in;

namespace server {

    server::Server::Server(char* rHost, char* rPort){
        cout << "Starting server..." << endl;
        mHost = rHost;
        mPort = rPort;
    }

    int server::Server::Initialisation(){
        void* address;
/*         char ipstr[20];
        int lPort = atoi(mPort); */

        mSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(mSock == SOCKET_ERROR){
            perror("ERROR: Failed to initialize server at socket creation");
            return SOCKET_ERROR;
        }

        if(getaddrinfo(mHost, mPort, NULL, &result) == SOCKET_ERROR){
            perror("ERROR: Failed to initialize server at getaddrinfo");
            return SOCKET_ERROR;
        }

        server_sockaddr_in = *(struct sockaddr_in *)result->ai_addr;
        address = &(server_sockaddr_in.sin_addr);

/*         inet_ntop(result->ai_family, address, ipstr, sizeof ipstr);
    
        server_sockaddr_in.sin_addr.s_addr = inet_addr(ipstr);
        server_sockaddr_in.sin_family = AF_INET;
        server_sockaddr_in.sin_port = htons(lPort); */

        if(bind(mSock, result->ai_addr, result->ai_addrlen) == -1){
            perror("ERROR: Failed to initialize server at bind");
            return SOCKET_ERROR;
        }

        cout << "Successfully initialized server" << endl;
    }

    int server::Server::Run(){
        cout << "Server is now listening on " << mHost << ":" << mPort << endl;

        while(1){
            if(listen(mSock, 10) == SOCKET_ERROR){
                perror("ERROR: Failed to listen");
            }
            sleep(1);
        }

        return 0;
    }


}