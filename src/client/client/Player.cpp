#include <client/Player.h>  // Included from library shared_static
#include "Player.h"

namespace client {
    void client::Player::SetStatusCommand(CommandID NewCommand){
        
        NotifyNewPlayerCommand();
    }

    CommandID client::Player::GetStatusCommand(){
        return this->mCommandStatus;
    }
}