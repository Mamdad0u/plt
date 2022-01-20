#include <client/Client.h>  // Included from library shared_static
#include "NetworkClient.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SOCKET_ERROR -1

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct addrinfo ADDRINFO;

struct addrinfo * result;
SOCKADDR_IN client_sockaddr_in = {0};

using namespace sf;
using namespace std;

namespace client{
    
    client::NetworkClient::NetworkClient(char* rHost, char* rPort){
        mHost = rHost;
        mPort = rPort;
    }


    int client::NetworkClient::ConnectTo(){
        socklen_t length = sizeof(client_sockaddr_in);
        mSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(mSock == SOCKET_ERROR){
            perror("ERROR: Failed to connect to server at socket creation");
            return SOCKET_ERROR;
        }

        if(getaddrinfo(mHost, mPort, NULL, &result) == SOCKET_ERROR){
            perror("ERROR: Failed to connect to server at getaddrinfo");
            return SOCKET_ERROR;
        }

        client_sockaddr_in = *(struct sockaddr_in *)result->ai_addr;

        if(connect(mSock, (sockaddr*)&client_sockaddr_in, length)  == SOCKET_ERROR){
            perror("ERROR: Failed to connect to server at connect");
            return SOCKET_ERROR;
        }

        mIsConnected = true;
    }

    int client::NetworkClient::RunNetwork(sf::RenderWindow& rWindow){
        char* buffer[128];

        while(mIsConnected){
            Event event;

            while (rWindow.pollEvent(event)){

                if ((event.type == Event::Closed)){
                    cout << "Closing window" << endl;
                    rWindow.close();
                    
                }
            
            }

            if(recv(mSock, buffer, sizeof(buffer), 0) != SOCKET_ERROR){
                cout << "Successfully received data from server" << endl;
            }

            else{
                perror("ERROR: Failed to retrieve data from server");
            }



        }


        return 0;
    }
}