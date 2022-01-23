#include <client/PlayerObserver.h>  // Included from library shared_static
#include "PlayerObserver.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

namespace client {

    client::PlayerObserver::~PlayerObserver(){

    }

    void PlayerObserver::NotifyNewPlayerCommand(){
        std::list<EngineObserver*>::iterator lIterator; 
        std::list<EngineObserver*>::const_iterator lConst_iterator;

        lIterator = mEngineObserverList.begin();
        lConst_iterator = mEngineObserverList.end();
        
        for(;lIterator!=lConst_iterator;++lIterator)
        {
          (*lIterator)->Update(this);
        }

    }

    void PlayerObserver::AddEngineObserver(EngineObserver* rNewobserver){
        mEngineObserverList.push_back(rNewobserver);
        rNewobserver->AddPlayerObserver(this);
        

    }





    
}