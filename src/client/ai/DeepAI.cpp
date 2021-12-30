#include <ai/DeepAI.h>  // Included from library shared_static
#include "DeepAI.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace client;
using namespace state;


namespace ai {

    ai::DeepAI::DeepAI(){
       
    }

/**
 * @brief Build tree of all game state possible over a depth define by @param rDepth value
 * 
 * @param rDepth Depth of tree
 */
    void ai::DeepAI::UpdateNodeTree(int rDepth){
        std::list<EngineObserver*>::iterator lRunningEngine;
        lRunningEngine = this->mEngineObserverList.begin(); // Get parameters and state of game engine
        State lGameStatus = (*lRunningEngine)->mCurrentState; // Get the state of the game
        Character* lActiveCharacter; // Active character for IA beeing played
        Character* lActiveEnemyCharacter; // Enemy character for IA beeing played
        Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();
        ActionList* lCharacterActionList = lActiveCharacter->GetActionList();

        if(lPlayerTurn == IA_MIN_TURN){ // Si c'est le tour de l'IA joueur  de jouer
            lActiveCharacter = lGameStatus.GetActivePlayerCharacter(); // Récupération du character actif de l'IA joueur en train d'être joué
            lActiveEnemyCharacter = lGameStatus.GetEnemyCharacter();
        }

        else if((lPlayerTurn == IA_MAX_TURN)){ //  Si c'est le tour de l'IA enemy de jouer
            lActiveCharacter = lGameStatus.GetEnemyCharacter(); // Récupération de son character
            lActiveEnemyCharacter = lGameStatus.GetActivePlayerCharacter();
        }
        
        for(int lIndex=0;lIndex<rDepth;lIndex++){ // Building tree over max rDepth
            





        }
    }


    /**
     * @brief Return a command based on minimax algorithm and node tree generated 
     * 
     * @return client::CommandID 
     */
    client::CommandID ai::DeepAI::GenerateDeepCommand(){
        
        std::list<EngineObserver*>::iterator lRunningEngine;
        lRunningEngine = this->mEngineObserverList.begin(); // Récupération des paramètres de l'engine 
        State lGameStatus = (*lRunningEngine)->mCurrentState; // Récupération de l'état du jeu depuis l'engine
        Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();

        UpdateNodeTree(3);

/*         if(lPlayerTurn == IA_MAX_TURN){

        }

        else if(lPlayerTurn == IA_MIN_TURN){
            
        } */


    }
    void ai::DeepAI::SetStatusCommand(client::CommandID rNewCommand){
        mInputCommand = rNewCommand;
        NotifyNewAICommand();
    }

    client::CommandID ai::DeepAI::GetStatusCommand() const{
        return this->mInputCommand;
    }

}