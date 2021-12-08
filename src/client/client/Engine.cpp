#include <client/Engine.h>  // Included from library shared_static
#include "Engine.h"
#include <algorithm>    // std::find
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>

using namespace std;

namespace client {

    client::Engine::Engine(){
        int lRandomPlayerCharacter;
        srand (time(NULL));
        
        lRandomPlayerCharacter = rand() % state::State::MAX_COMBAT_NB;

        int lRandomInt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::random_shuffle(lRandomInt, lRandomInt + state::State::MAX_COMBAT_NB);

            for(int lIndex=0;lIndex<state::State::MAX_COMBAT_NB; lIndex++){

                mRandomEnemyList[lIndex] = (state::CharacterName)lRandomInt[lIndex];

            }



        mCurrentState.AddPlayerCharacter((state::CharacterName)lRandomPlayerCharacter);
        mCurrentState.AddEnemyCharacter(mRandomEnemyList[0]);
    }

    state::CombatStatus client::Engine::GameLoop(){
       
        state::CombatStatus lGameStatus = mCurrentState.GetCombatState();
        state::Player_Status lPlayerStatus = mCurrentState.GetPlayerStatus();

        
        switch (lGameStatus)
        {

        case state::GAME_OVER:
            cout << "You loose on combat " << mCurrentState.GetCombatNumber() << endl;
            
            break;

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
                    mCurrentState.MoveActivePlayer();
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

            else if(mCurrentState.GetPlayerRosterSize() > mCurrentState.MAX_CHARACTER){
                cout << "Equipe pleine ! " << endl;
            }

            mCurrentState.MoveNextCombat();
            mCurrentState.AddEnemyCharacter(mRandomEnemyList[mCurrentState.GetCombatNumber()]);
            mCurrentState.SetCombatState(state::IN_COMBAT);
            break;

        
        
        
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