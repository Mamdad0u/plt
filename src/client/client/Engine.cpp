#include <client/Engine.h>  // Included from library shared_static
#include "Engine.h"
#include <iostream>

using namespace std;

namespace client {
    client::Engine::Engine(){
        /*INITIALISATION*/

        /*TEST*/
        
        state::Character UUT_Character_IS("IS", state::INFO, state::ALIVE);
        state::Character UUT_Character_SIA("SIA", state::SIGNAL, state::ALIVE);

        UUT_Character_IS.SetCharacterStats(state::LIFE_POINTS, 80);
        UUT_Character_IS.SetCharacterStats(state::ATTACK, 140);
        UUT_Character_IS.SetCharacterStats(state::POWER, 140);
        UUT_Character_IS.SetCharacterStats(state::DEFENSE, 80);
        UUT_Character_IS.SetCharacterStats(state::LUCK, 5);
        UUT_Character_IS.SetCharacterAction(state::ATTACK_1, 80, state::LUCK, 3, true);
        UUT_Character_IS.SetCharacterAction(state::ATTACK_2, 60, state::LUCK, 0, true);



        UUT_Character_SIA.SetCharacterStats(state::LIFE_POINTS, 110);
        UUT_Character_SIA.SetCharacterStats(state::ATTACK, 80);
        UUT_Character_SIA.SetCharacterStats(state::POWER, 150);
        UUT_Character_SIA.SetCharacterStats(state::DEFENSE, 60);
        UUT_Character_SIA.SetCharacterStats(state::LUCK, 3);
        UUT_Character_SIA.SetCharacterAction(state::ATTACK_1, 80, state::LUCK, 0, true); 

        mCurrentState.AddPlayerCharacter(*(&UUT_Character_IS));
        mCurrentState.AddEnemyCharacter(*(&UUT_Character_SIA));
    }

    void client::Engine::GameLoop(){
       
        state::CombatStatus lGameStatus = mCurrentState.GetCombatState();
        state::Player_Status lPlayerStatus = mCurrentState.GetPlayerStatus();
        state::Character lActivePlayerCharacter = *(mCurrentState.GetActivePlayerCharacter());
        state::Character lEnemyCharacter = *(mCurrentState.GetEnemyCharacter());
        
        switch (lGameStatus)
        {
        case state::IN_COMBAT:
            switch (lPlayerStatus)
            {
            case state::PLAYER_TURN:
                if(mIsNewPlayerCommand){ // 1. Wait for input command

                    mCommand.ComputeAction(*(&lActivePlayerCharacter), *(&lEnemyCharacter), mInputCommandID);
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

                mCurrentState.SetPlayerStatus(state::PLAYER_TURN);
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
        this->mInputCommandID = rNewCommand;
        this->mIsNewPlayerCommand = true;
    }


}