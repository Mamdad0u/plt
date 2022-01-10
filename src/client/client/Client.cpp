#include <client/Client.h>  // Included from library shared_static
#include <thread>
#include <mutex>

using namespace client;
using namespace std;

namespace client{

/**
 * @brief Construct a new client::Client::Client object
 * Initiate game engine thread
 * 
 */
    client::Client::Client(){
        
    }

    void client::Client::ThreadEngine(engine::Engine* rEngine){

    }

    void client::Client::Run(){
        thread t1(ThreadEngine, mEngine);
    }






}