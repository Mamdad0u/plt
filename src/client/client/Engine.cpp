#include <client/Engine.h>  // Included from library shared_static
#include "Engine.h"
#include <iostream>

using namespace std;

namespace client {

    client::Engine::Engine(){
        mCurrentState.AddPlayerCharacter(state::IS);
    }

    state::CombatStatus client::Engine::GameLoop(){
       
        state::CombatStatus lGameStatus = mCurrentState.GetCombatState();
        state::Player_Status lPlayerStatus = mCurrentState.GetPlayerStatus();

        
        switch (lGameStatus)
        {

        
        case state::INITIALISATION:
            if(mCurrentState.GetPlayerRosterSize() < 1){
                cout << "Waiting for player to choose a character" << endl;
            }

            else if(mCurrentState.GetEnemyRosterSize() < 1){
                cout << "Waiting for enemy to choose a character" << endl;
            }

            else{
                mCurrentState.SetCombatState(state::IN_COMBAT);
            }
            break;

        case state::IN_COMBAT:
            switch (lPlayerStatus)
            {
            case state::PLAYER_TURN:
                if(mIsNewPlayerCommand){ // 1. Wait for input command

                    mCommand.ComputeAction(*(mCurrentState.GetActivePlayerCharacter()), *(mCurrentState.GetEnemyCharacter()), mInputCommandID); // Le joueur attaque l'IA
                    mIsNewPlayerCommand = false; // The command has been executed
                    mCurrentState.SetPlayerStatus(state::IA_TURN); // Give the turn to opponent 
                    
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
                if(mIsNewAICommand){
                    mCommand.ComputeAction(*(mCurrentState.GetEnemyCharacter()), *(mCurrentState.GetActivePlayerCharacter()), mInputCommandID); // L'IA attaque le joueur

                }
                mIsNewAICommand = false;
                mCurrentState.SetPlayerStatus(state::PLAYER_TURN);
                break;
            



            }
            
            mCurrentState.SetAlivePlayer();
            mCurrentState.SetAliveEnemy();

            if(mCurrentState.GetAlivePlayer() == false){
                mCurrentState.SetCombatState(state::GAME_OVER);

            }

            if(mCurrentState.GetAliveEnemy() == false){
                mCurrentState.SetCombatState(state::OUT_COMBAT);
            }
            break;
        

        case state::OUT_COMBAT:
            /*Player win, adding the enemy in his roster*/
            state::Character* lActiveEnemy  = mCurrentState.GetEnemyCharacter();
            if(mCurrentState.GetPlayerRosterSize() < mCurrentState.MAX_CHARACTER){
                mCurrentState.AddPlayerCharacter(lActiveEnemy->GetCharacterNameNumber());
            }

            break;

            // Check alive player 

        }
        // Check alive player 


        return mCurrentState.GetCombatState();
        
    }


    state::CombatStatus client::Engine::DEBUG_GetGameStatus(){

        return mCurrentState.GetCombatState();
    }

    void client::Engine::UpdatePlayerCommandStatus(CommandID rNewCommand){
        this->mInputCommandID = rNewCommand;
        this->mIsNewPlayerCommand = true;
    }


}