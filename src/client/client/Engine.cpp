#include <client/Engine.h>  // Included from library shared_static
#include "Engine.h"

namespace client {
    client::Engine::Engine(){
        /*INITIALISATION*/

        

    }

    void client::Engine::GameLoop(){
        
        state::CombatStatus lGameStatus = mCurrentState.GetCombatState();
        state::Player_Status lPlayerStatus = mCurrentState.GetPlayerStatus();
        state::Character lActiveCharacter = mCurrentState.GetActivePlayerCharacter();
        
        switch (lGameStatus)
        {
        case state::IN_COMBAT:
            switch (lPlayerStatus)
            {
            case state::PLAYER_TURN:
                if(mIsNewPlayerCommand){ // 1. Wait for input command
                    

                    

                    mCurrentState.SetPlayerStatus(state::IA_TURN); // Give the turn to opponent 
                    mIsNewPlayerCommand = false; // The command has been executed
                }

            /*  1. Wait for input command
                2. Interprete command
                3. Execute command
                4. Move next turn                
                */
               


                break;
            
            case state::IA_TURN:
            /*  1. Wait for input command
                2. Interprete command
                3. Execute command
                4. Move next turn                
                */
                break;
            
            default:
                break;
            }
            break;
        
        case state::OUT_COMBAT:

            break;

            // Check alive player 
        }


        
        
    }


    state::CombatStatus client::Engine::DEBUG_GetGameStatus(){

        return mCurrentState.GetCombatState();
    }

    void client::Engine::UpdatePlayerCommandStatus(CommandID rNewCommand){
        this->mIsNewPlayerCommand = true;
    }


}