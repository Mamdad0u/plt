#include <ai/DeepAI.h>  // Included from library shared_static
#include "DeepAI.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace client;
using namespace state;
using namespace std;

namespace ai {

    ai::DeepAI::DeepAI(){ 
       mNodeNumber.reserve(5); 
       mNodeNumber.push_back(1); //Root of the tree
    }

/**
 * @brief Build tree of all game state possible over a depth define by @param rDepth value
 * 
 * @param rDepth Depth of tree()
 */
    void ai::DeepAI::UpdateNodeTree(int rDepth){
        
        int lNode_Number = 0; // Number of nodes created at the depth tested
        state::ActionListCommand lAction_Type[] = {state::ATTACK_1, state::ATTACK_2, state::SPELL_1, state::SPELL_2};
        
        EngineObserver* lRunningEngine;// Actual game engine running the game
            
        lRunningEngine = *(mEngineObserverList.begin());  // Get parameters and state of game engine
       
        //lTestEngine = lRunningEngine;
        // SandBoxEngine* lTestEngine; // Test engine in sandbox environnement to test action
        
        State lGameStatus = lRunningEngine->mCurrentState; // Get the state of the game
        
        Character* lActiveCharacter; // Active character for IA beeing played
        Character* lActiveEnemyCharacter; // Enemy character for IA beeing played
        Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();
        Action* lActiveCharacter_Action = nullptr; 

        
        SandBoxEngine lTestEngine(lGameStatus);

        Node lPrimary_Root_Node(lGameStatus, 0); // FIrst node of the tree
        lPrimary_Root_Node.SetIndex(0);
        Node lRoot_Node;

        if(lPlayerTurn == IA_MIN_TURN){ // Si c'est le tour de l'IA joueur  de jouer
            lActiveCharacter = lGameStatus.GetActivePlayerCharacter(); // Récupération du character actif de l'IA joueur en train d'être joué
            lActiveEnemyCharacter = lGameStatus.GetEnemyCharacter();
        }

        else if((lPlayerTurn == IA_MAX_TURN)){ //  Si c'est le tour de l'IA enemy de jouer
            lActiveCharacter = lGameStatus.GetEnemyCharacter(); // Récupération de son character
            lActiveEnemyCharacter = lGameStatus.GetActivePlayerCharacter();
        }
        
        
        for(int lIndex_Depth=0;lIndex_Depth<=rDepth;lIndex_Depth++){ // Building tree over max rDepth
            
            for(int lIndex_Node_Number = 0; lIndex_Node_Number<mNodeNumber[lIndex_Depth]; lIndex_Node_Number++){ // Each node present at the depth beeing computed
                
                if(lIndex_Depth > 0){ // If not the primary root node
                    lRoot_Node = *(lPrimary_Root_Node.GetBranch(lIndex_Node_Number));
                    lGameStatus = *(lRoot_Node.GetGameContext()); // Get the game context of the node to test his childs nodes
                    lTestEngine.SetGameContext(lGameStatus); // Set Test engine to node game context
                    
                    lPlayerTurn = lGameStatus.GetPlayerStatus();
                    if(lPlayerTurn == IA_MIN_TURN){ // Si c'est le tour de l'IA joueur  de jouer
                        lActiveCharacter = lGameStatus.GetActivePlayerCharacter(); // Récupération du character actif de l'IA joueur en train d'être joué
                        lActiveEnemyCharacter = lGameStatus.GetEnemyCharacter();
                    }

                    else if((lPlayerTurn == IA_MAX_TURN)){ //  Si c'est le tour de l'IA enemy de jouer
                        lActiveCharacter = lGameStatus.GetEnemyCharacter(); // Récupération de son character
                        lActiveEnemyCharacter = lGameStatus.GetActivePlayerCharacter();
                    }
        
                
                
                }

                else{ // Only for primary root node
                   lRoot_Node = lPrimary_Root_Node;
                }
                
                

                for(int lIndex_Character_Action = 0; lIndex_Character_Action<4;lIndex_Character_Action++){ // Each character have 4 max action
                    lActiveCharacter_Action = lActiveCharacter->GetAction(lAction_Type[lIndex_Character_Action]); // Get each action of the active character beeing played

                    if(lActiveCharacter_Action->GetDamage() != 0){ // If action exists on the character (case where a charcter dont have an action specified (ex SPELL_2, etc))
                        Node* lNewNode = new Node;
                        *(lNewNode) = lTestEngine.TestAction(*(lActiveCharacter), *(lActiveEnemyCharacter), lAction_Type[lIndex_Character_Action]); //Test the next game state if we execute this action in a new node
                        lNewNode->SetIndex(lIndex_Depth+1); // The depth of the node defined his index
                        lRoot_Node.AddBranch(lNewNode); // Add the node created in a branch to the root node 
                        lTestEngine.SetGameContext(lGameStatus); // And reset game context in root node for next action to test
                        lNode_Number++;
                    }
                }
                
            }

            if(lIndex_Depth == 0){
                lPrimary_Root_Node = lRoot_Node;
            }

            mNodeNumber.push_back(lNode_Number); // Add the number of nodes at the depth + 1
            lNode_Number = 0; // And reset it for next depth



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