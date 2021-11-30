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


        

        /* UUT_Character_IS.SetCharacterStats(state::LIFE_POINTS, 80);
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
        UUT_Character_SIA.SetCharacterAction(state::ATTACK_1, 80, state::LUCK, 0, true);  */
/* 
        mCurrentState.AddPlayerCharacter(*(&UUT_Character_SIA));
        mCurrentState.AddEnemyCharacter(*(&UUT_Character_IS)); */
    }

    state::CombatStatus client::Engine::GameLoop(){
       
        state::CombatStatus lGameStatus = mCurrentState.GetCombatState();
        state::Player_Status lPlayerStatus = mCurrentState.GetPlayerStatus();

        
        switch (lGameStatus)
        {
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
            if(mCurrentState.GetPlayerRosterSize() < mCurrentState.MAX_CHARACTER){
                mCurrentState.AddPlayerCharacter(*(mCurrentState.GetEnemyCharacter()));
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