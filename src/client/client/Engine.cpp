#include <client/Engine.h>  // Included from library shared_static
#include "Engine.h"

namespace client {
    client::Engine::Engine(){


    }

    state::CombatStatus client::Engine::DEBUG_GetGameStatus(){

        return mCurrentState.GetCombatState();
    }


}