#include <client/PlayerObserver.h>  // Included from library shared_static
#include "PlayerObserver.h"

namespace client {
    void PlayerObserver::NotifyNewPlayerCommand(){
        mEngineObserver.UpdatePlayerCommandStatus(this->mCommandStatus);


    }
    
}