#include <client/SandBoxEngine.h>  // Included from library shared_static
#include "SandBoxEngine.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
using namespace state;
using namespace ai;
namespace client {


    client::SandBoxEngine::SandBoxEngine(state::State& rNewGameContext){

      this->mCurrentState = rNewGameContext;

    }



    ai::Node client::SandBoxEngine::TestAction(state::Character& rAttacker, state::Character& rVictim, state::ActionListCommand rActionToTest){
        Player_Status lPlayerTurn = mCurrentState.GetPlayerStatus();
        int lActionValue = 0;
        int lNode_score = 0;
        int lAliveCharacters_Player  = mCurrentState.GetAlivePlayer();

        /**
         * @brief Firstly, we test the action, depending of its type defined by rActionToTest. We grab the value of the action made,
         * positive if PV gain (beneficial action), negative if PV lost (negative action)
         * 
         * 
         */
        if(lPlayerTurn == IA_MAX_TURN){
            lActionValue = mCommand_IA_MAX.ComputeAction(*(mCurrentState.GetEnemyCharacter()), *(mCurrentState.GetActivePlayerCharacter()), (CommandID)rActionToTest);        
        }

        else if(lPlayerTurn == IA_MIN_TURN){
            lActionValue =  mCommand_IA_MIN.ComputeAction(*(mCurrentState.GetActivePlayerCharacter()), *(mCurrentState.GetEnemyCharacter()), (CommandID)rActionToTest);
        }
        /*Update the state of all players with action tested*/
        mCurrentState.SetAlivePlayer();
        mCurrentState.SetAliveEnemy();
        
        /**
         * @brief Secondly, we analyze the result of the action done, to caracterize the type of node happened with this action.
         * 
         */
      //  Node lNewNode(mCurrentState, NODE_GAME_WIN);

        //If all players characters died with this action 
        if(mCurrentState.GetAlivePlayer() == 0){
            lNode_score = NODE_GAME_OVER;
            Node lNewNode(mCurrentState, lNode_score);
            return lNewNode;
        }

        //If one of the player characters died with this action
        else if(mCurrentState.GetAlivePlayer() < lAliveCharacters_Player){
            lNode_score = NODE_CHARACTER_PLAYER_DEAD;
            Node lNewNode(mCurrentState, lNode_score);
            return lNewNode;
        }

        //If the enemy character died with the action (IA MIN or PLAYER turn only)
        else if(mCurrentState.GetAliveEnemy() == false){
            lNode_score = NODE_NEXT_COMBAT;
            Node lNewNode(mCurrentState, lNode_score);
            return lNewNode;
        }
        
        //Else, all other cases :

        else{
            // If the action make a PV lost
            if(lActionValue < 0){
                lNode_score = (lActionValue * NODE_PV_LOST_ACTION) * (-1);
                Node lNewNode(mCurrentState, lNode_score);
                return lNewNode;
            }

            // If the action make a PV gain
            else if(lActionValue > 0){
                lNode_score = lActionValue * NODE_PV_GAIN_ACTION * (-1);
                Node lNewNode(mCurrentState, lNode_score);
                return lNewNode;
            }


        }

    }




}