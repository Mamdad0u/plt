#include <client/Engine.h>  // Included from library shared_static
#include "Engine.h"
#include <algorithm>    // std::find
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
#include <string.h>

using namespace std;
using namespace state;

namespace client {
/**
 * @brief Construct a new client::Engine::Engine object
 * Setting up game state : random enemy character for each combat
 * 
 */
    client::Engine::Engine(){
        int lRandomPlayerCharacter;
        int lIndex2 = 0;
        srand (time(NULL));
        
        lRandomPlayerCharacter = rand() % state::State::MAX_COMBAT_NB;

        int lRandomInt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::random_shuffle(lRandomInt, lRandomInt + state::State::MAX_COMBAT_NB);
    //    lRandomPlayerCharacter = 7;
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

    void client::Engine::ResetEngine() {

        int lIndex2 = 0;
        int lRandomPlayerCharacter;

        int lRandomInt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

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
            char playerAnswer[1];
            cout << "You loose on combat " << mCurrentState.GetCombatNumber() <<" , Arena " << mCurrentState.GetArenaNumber() << endl;
            cout << "Try again ? (y/n)" << endl;
            cin >> playerAnswer;

            if(strcmp(playerAnswer,"y") == 0) {

                cout << "New game will launch." << endl;
                
                //mCurrentState.SetAlivePlayer();
                //mCurrentState.SetAliveEnemy();

                mCurrentState.SetCombatState(state::INITIALISATION);
                
            }

            if(strcmp(playerAnswer,"n") == 0) {

                cout << "Ok, looser." << endl;
            }
            
            
            break;

        case state::INITIALISATION:
            if(mCurrentState.GetPlayerRosterSize() < 1){
                cout << "Waiting for player to choose a character" << endl;
            }

            else if(mCurrentState.GetEnemyRosterSize() < 1){
                cout << "Waiting for enemy to choose a character" << endl;
            }

            if(mIsRenderEnded){
                mCurrentState.SetCombatState(state::IN_COMBAT);
                mIsRenderEnded = false;
            }
            break;

        case state::IN_COMBAT:
            switch (lPlayerStatus)
            {
            case state::PLAYER_TURN:
                if(mIsNewPlayerCommand){ /// 1. Wait for input command. Add mIsNewAICommand if player is played by AI
                    mCurrentState.MoveActivePlayer();
                    mCommand_Player.ComputeAction(*(mCurrentState.GetActivePlayerCharacter()), *(mCurrentState.GetEnemyCharacter()), mInputCommandID); // Le joueur attaque l'IA
                    mIsNewPlayerCommand = false; // The command has been executed
                    mCurrentState.SetPlayerStatus(state::IA_MAX_TURN); // Give the turn to opponent 
                    mCurrentState.MoveNextTurn();
                }

                // else{
                //     cout << "Waiting for player to input a command" << endl;
                // }

            /*  1. Wait for input command
                2. Interprete command
                3. Execute command
                4. Move next turn                
                */

                break;
            case state::IA_MIN_TURN: // Player played by IA
                if(mIsNewAICommand){
                    mCurrentState.MoveActivePlayer();
                    mCommand_IA_MIN.ComputeAction(*(mCurrentState.GetActivePlayerCharacter()), *(mCurrentState.GetEnemyCharacter()), mInputCommandID); // L'IA attaque le joueur
                    mIsNewAICommand = false;
                    mCurrentState.SetPlayerStatus(state::IA_MAX_TURN);
                    mCurrentState.MoveNextTurn();
                }
                break;
            case state::IA_MAX_TURN:
            /*  1. Wait for input command
                2. Interprete command
                3. Execute command
                4. Move next turn                
                */
                if(mIsNewAICommand){
                    mCommand_IA_MAX.ComputeAction(*(mCurrentState.GetEnemyCharacter()), *(mCurrentState.GetActivePlayerCharacter()), mInputCommandID); // L'IA attaque le joueur
                    mIsNewAICommand = false;

                    if(mPlayerIA){ // If player played by an IA
                        mCurrentState.SetPlayerStatus(state::IA_MIN_TURN); // Next turn for IA MIN
                    }
                    else{
                        mCurrentState.SetPlayerStatus(state::PLAYER_TURN); // Else for human player
                    }
                    
                    mCurrentState.MoveNextTurn();
                }

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