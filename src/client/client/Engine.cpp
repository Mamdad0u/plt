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
        int lIndex2 = 0;
        srand (time(NULL));
        
        lRandomPlayerCharacter = rand() % state::State::MAX_COMBAT_NB;

        int lRandomInt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::random_shuffle(lRandomInt, lRandomInt + state::State::MAX_COMBAT_NB);
       // lRandomPlayerCharacter = 2;
        mCurrentState.AddPlayerCharacter((state::CharacterName)lRandomPlayerCharacter);
        
       
            for(int lIndex=0;lIndex<state::State::MAX_COMBAT_NB; lIndex++){
                if((state::CharacterName)lRandomInt[lIndex] != (state::CharacterName)lRandomPlayerCharacter){
                    mRandomEnemyList[lIndex] = (state::CharacterName)lRandomInt[lIndex2];
                    lIndex2++;
                }

                else{
                    lIndex2+=1;
                    mRandomEnemyList[lIndex] = (state::CharacterName)lRandomInt[lIndex2];
                    lIndex2+=1;
                }
                
                

            }




        mCurrentState.AddEnemyCharacter(mRandomEnemyList[0]);
    }

    state::State* client::Engine::GameLoop(){
       
        state::CombatStatus lGameStatus = mCurrentState.GetCombatState();
        state::Player_Status lPlayerStatus = mCurrentState.GetPlayerStatus();
        int lTurn = mCurrentState.GetTurn();
        int lArena = mCurrentState.GetArenaNumber();
        int lMax_Combat = mCurrentState.GetCombatPerArena();
        int lCombatNumber = mCurrentState.GetCombatNumber();

        switch (lGameStatus)
        {

        case state::RENDER_PROCESSING:
            if(mIsRenderEnded){
                mCurrentState.SetCombatState(state::IN_COMBAT);
                mIsRenderEnded = false;
            }


            break;



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
                    mCommand_Player.ComputeAction(*(mCurrentState.GetActivePlayerCharacter()), *(mCurrentState.GetEnemyCharacter()), mInputCommandID); // Le joueur attaque l'IA
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
                    mCommand_IA.ComputeAction(*(mCurrentState.GetEnemyCharacter()), *(mCurrentState.GetActivePlayerCharacter()), mInputCommandID); // L'IA attaque le joueur

                }
                mIsNewAICommand = false;
                mCurrentState.SetPlayerStatus(state::PLAYER_TURN);
                break;
            



            }
            
            mCurrentState.SetAlivePlayer();
            mCurrentState.SetAliveEnemy();

            if(mCurrentState.GetAlivePlayer() == 0){
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
            lCombatNumber = mCurrentState.GetCombatNumber();

            if(lCombatNumber > lMax_Combat){ // Si l'arêne est terminée
                mCurrentState.GoToNextArena(); // On va à l'arêne suivante
                mCurrentState.ResetCombatNumber();
            }



            mCurrentState.AddEnemyCharacter(mRandomEnemyList[mCurrentState.GetCombatNumber()]);
            mCurrentState.SetCombatState(state::RENDER_PROCESSING);
            break;


        // Check alive player 


        
        
    }
    return &mCurrentState;
}

    state::CombatStatus client::Engine::DEBUG_GetGameStatus(){

        return mCurrentState.GetCombatState();
    }

    void client::Engine::UpdatePlayerCommandStatus(CommandID rNewCommand){
        this->mInputCommandID = rNewCommand;
        this->mIsNewPlayerCommand = true;
    }


    


}