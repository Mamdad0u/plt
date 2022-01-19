#include <server.h>
#include <iostream>
#include <string.h>

using namespace std;
using namespace server;

int main(int argc,char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "listen") == 0){
            cout << "Starting server..." << endl;
        }


    }
    return 0;
}