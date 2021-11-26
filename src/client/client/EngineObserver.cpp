#include <client/EngineObserver.h>  // Included from library shared_static
#include "EngineObserver.h"
#include <iostream>
#include <map>
using namespace std;

namespace client {
    client::EngineObserver::EngineObserver(){
       

        
        
    }
    
    void client::EngineObserver::AddPlayerObserver(PlayerObserver* rNewObserver){
        mPlayerObserverList.push_back(rNewObserver);
        
        


    }


    void client::EngineObserver::DelPlayerObserver(PlayerObserver* rNewObserver){
/*         std::list<EngineObserver*>::iterator lIterator; 
        std::list<EngineObserver*>::const_iterator lConst_iterator;

        lIterator = mPlayerObserverList.begin();
        
        for(;lIterator!=lConst_iterator;++lIterator)
        {
          (*lIterator)->DelPlayerObserver(this);
        } */




    }

    void client::EngineObserver::Update ( PlayerObserver* rNewPlayerObserver) {
        std::map<CommandID,std::string> lCommandIDStringMap;
        lCommandIDStringMap[ATTACK_1] = "ATTACK 1";
        lCommandIDStringMap[ATTACK_2] = "ATTACK 2";
        lCommandIDStringMap[SPELL_1] = "SPELL 1";
        lCommandIDStringMap[SPELL_2] = "SPELL 2";

        cout << "New player action is " << lCommandIDStringMap[rNewPlayerObserver->GetStatusCommand()] << endl;
        
        mInputCommandID = rNewPlayerObserver->GetStatusCommand();
        mIsNewPlayerCommand = true;
    }



}