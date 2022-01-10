#include <engine/EngineObserver.h>  // Included from library shared_static
#include "EngineObserver.h"
#include <iostream>
#include <map>
using namespace std;

namespace engine {
    engine::EngineObserver::EngineObserver(){
       

        
        
    }
    
    void engine::EngineObserver::AddPlayerObserver(PlayerObserver* rNewObserver){
        mPlayerObserverList.push_back(rNewObserver);
        


    }

    void engine::EngineObserver::AddAIObserver(ai::AIObserver* rNewObserver){
        int lAIObserverList_Size = 0;
        mAIObserverList.push_back(rNewObserver);
        lAIObserverList_Size = mAIObserverList.size();

        if(lAIObserverList_Size == 2){  /**
         * @brief This condition allows to detect if player is played by an IA.
         * If IA playing the player, 2 IA playing in the game so player is played by IA.
         */
            mPlayerIA = true;
            mCurrentState.SetPlayerStatus(state::IA_MAX_TURN); // Setting up first turn for IA MAX 
        }
    }
    
    void engine::EngineObserver::DelPlayerObserver(PlayerObserver* rNewObserver){
/*         std::list<EngineObserver*>::iterator lIterator; 
        std::list<EngineObserver*>::const_iterator lConst_iterator;

        lIterator = mPlayerObserverList.begin();
        
        for(;lIterator!=lConst_iterator;++lIterator)
        {
          (*lIterator)->DelPlayerObserver(this);
        } */




    }

    void engine::EngineObserver::Update ( PlayerObserver* rNewPlayerObserver) {
        std::map<CommandID,std::string> lCommandIDStringMap;
        lCommandIDStringMap[ATTACK_1] = "ATTACK 1";
        lCommandIDStringMap[ATTACK_2] = "ATTACK 2";
        lCommandIDStringMap[SPELL_1] = "SPELL 1";
        lCommandIDStringMap[SPELL_2] = "SPELL 2";

        cout << "New player action is " << lCommandIDStringMap[rNewPlayerObserver->GetStatusCommand()] << endl;
        
        mInputCommandID = rNewPlayerObserver->GetStatusCommand();
        mIsNewPlayerCommand = true;
       
    }

    void engine::EngineObserver::Update ( ai::AIObserver* rNewAIObserver) {
        std::map<CommandID,std::string> lCommandIDStringMap;
        lCommandIDStringMap[ATTACK_1] = "ATTACK 1";
        lCommandIDStringMap[ATTACK_2] = "ATTACK 2";
        lCommandIDStringMap[SPELL_1] = "SPELL 1";
        lCommandIDStringMap[SPELL_2] = "SPELL 2";

        cout << "New AI action is " << lCommandIDStringMap[rNewAIObserver->GetStatusCommand()] << endl;
        
        mInputCommandID = rNewAIObserver->GetStatusCommand();
        
        mIsNewAICommand = true;

    }
void engine::EngineObserver::Update(render::RenderObserver* rNewRenderObserver) {

    mIsRenderEnded = true;

}

void engine::EngineObserver::AddRenderObserver(render::RenderObserver* rNewRenderObserver) {

    mRenderObserverList.push_back(rNewRenderObserver);

}



}

