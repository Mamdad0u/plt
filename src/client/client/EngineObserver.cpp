#include <client/EngineObserver.h>  // Included from library shared_static
#include "EngineObserver.h"

namespace client {
    client::EngineObserver::EngineObserver(){
       

        
        
    }
    
    void client::EngineObserver::AddPlayerObserver(PlayerObserver* rNewObserver){
        mPlayerObserverList.push_back(rNewObserver);

        


    }


    void client::EngineObserver::DelPlayerObserver(PlayerObserver* rNewObserver){





    }

    void client::EngineObserver::Update (const PlayerObserver* rNewCommand) const{
        // this->mInputCommandID = rNewCommand;
        // this->mIsNewPlayerCommand = true;
    }


}