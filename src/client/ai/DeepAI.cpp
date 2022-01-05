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
        mNodeTree.reserve(85); // Arbitrary
        mNodeNumber.reserve(85); // Arbitrary      
        mNodeNumber.push_back(1); //Root of the tree
    }

/**
 * @brief Build tree of all game state possible over a depth define by @param rDepth value
 * 
 * @param rDepth Depth of tree()
 */
    void ai::DeepAI::UpdateNodeTree(int rDepth){
        
        int lNode_Number = 0; // Number of nodes created at the depth tested
        int lNode_Sum = 0; // Sum of nodes created
        state::ActionListCommand lAction_Type[] = {state::ATTACK_1, state::ATTACK_2, state::SPELL_1, state::SPELL_2};
        
        EngineObserver* lRunningEngine;// Actual game engine running the game
            
        lRunningEngine = *(mEngineObserverList.begin());  // Get parameters and state of game engine
       

        
        State lGameStatus = lRunningEngine->mCurrentState; // Get the state of the game
        lGameStatus.SetDebugInfo(false); //Disable game output in terminal

        Character* lActiveCharacter; // Active character for IA beeing played
        Character* lActiveEnemyCharacter; // Enemy character for IA beeing played
        Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();
        Action* lActiveCharacter_Action = nullptr; 

        
        SandBoxEngine lTestEngine(lGameStatus);  // Test engine in sandbox environnement to test action

        Node lPrimary_Root_Node(lGameStatus, 0); // First node of the tree
        lPrimary_Root_Node.SetIndex(0);

        mNodeTree.push_back(&lPrimary_Root_Node);
        lNode_Sum++;


        Node lParent_Node;

        if(lPlayerTurn == IA_MIN_TURN){ // Si c'est le tour de l'IA joueur  de jouer
            lActiveCharacter = lGameStatus.GetActivePlayerCharacter(); // Récupération du character actif de l'IA joueur en train d'être joué
            lActiveEnemyCharacter = lGameStatus.GetEnemyCharacter();
        }

        else if((lPlayerTurn == IA_MAX_TURN)){ //  Si c'est le tour de l'IA enemy de jouer
            lActiveCharacter = lGameStatus.GetEnemyCharacter(); // Récupération de son character
            lActiveEnemyCharacter = lGameStatus.GetActivePlayerCharacter();
        }
        
        
        for(int lIndex_Depth=0;lIndex_Depth<rDepth;lIndex_Depth++){ // Building tree over max rDepth

            for(int lIndex_Node_Number = 0; lIndex_Node_Number<mNodeNumber[lIndex_Depth]; lIndex_Node_Number++){ // Each node present at the depth beeing computed
                

                if(lIndex_Depth > 0){ // If not the primary root node
                    lParent_Node = *(mNodeTree[(lNode_Sum-1) - lIndex_Node_Number]); // Getting each parent present ath the depth
                    lGameStatus = *(lParent_Node.GetGameContext()); // Get the game context of the parent node to test his childs nodes
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
                   lParent_Node = lPrimary_Root_Node;
                }
                
                
                if(lParent_Node.GetNodeValue() != (int)NODE_GAME_OVER){ // If parent node is not a GAME_OVER node
                    for(int lIndex_Character_Action = 0; lIndex_Character_Action<4;lIndex_Character_Action++){ // Each character have 4 max action
                        lActiveCharacter_Action = lActiveCharacter->GetAction(lAction_Type[lIndex_Character_Action]); // Get each action of the active character beeing played

                            if((lActiveCharacter_Action->GetDamage() != 0)){ // If action exists on the character (case where a charcter dont have an action specified (ex SPELL_2, etc)),  
                                Node* lNewChildNode = new Node;
                                *(lNewChildNode) = lTestEngine.TestAction(lAction_Type[lIndex_Character_Action]); //Test the next game state if we execute this action in a new node
                                lNewChildNode->SetIndex(lIndex_Depth+1); // The depth of the node defined his index
                                lParent_Node.AddBranch(lNewChildNode); // Add the node created in a branch to the root node 
                                lTestEngine.SetGameContext(lGameStatus); // And reset game context in root node for next action to test
                                lNode_Number++;
                                mNodeTree.push_back(lNewChildNode); // Add the child node to the parent tree,, so he can become a parent at depth + 1
                            }
                    }
                }

                
            }
            /*Necessary to get the primary root node of the tree*/
            if(lIndex_Depth == 0){
                lPrimary_Root_Node = lParent_Node;
            }

            mNodeNumber.push_back(lNode_Number); // Add the number of nodes at the depth + 1
            lNode_Sum += lNode_Number;
            lNode_Number = 0; // And reset it for next depth



        }
    }



    /**
     * @brief Return a command based on minimax algorithm and node tree generated 
     * 
     * @return client::CommandID 
     */
    client::CommandID ai::DeepAI::GenerateDeepCommand(int rDepth){
        
        std::list<EngineObserver*>::iterator lRunningEngine;
        lRunningEngine = this->mEngineObserverList.begin(); // Récupération des paramètres de l'engine 
        State lGameStatus = (*lRunningEngine)->mCurrentState; // Récupération de l'état du jeu depuis l'engine
        Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();

        UpdateNodeTree(rDepth); // First generate the tree of game possibilities from 0 to depth
        cout << "Finished" << endl;

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