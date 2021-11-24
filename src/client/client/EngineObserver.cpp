#include <client/EngineObserver.h>  // Included from library shared_static
#include "EngineObserver.h"

namespace client {
    client::EngineObserver::EngineObserver(){
       

        
        
    }


    void client::EngineObserver::UpdatePlayerCommandStatus(CommandID rNewCommand){
        this->mInputCommandID = rNewCommand;
        this->mIsNewPlayerCommand = true;
    }


}