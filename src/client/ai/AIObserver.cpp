#include <ai/AIObserver.h>  // Included from library shared_static
#include "AIObserver.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace engine;

namespace ai {

    void ai::AIObserver::NotifyNewAICommand(){
        std::list<EngineObserver*>::iterator lIterator; 
        std::list<EngineObserver*>::const_iterator lConst_iterator;

        lIterator = mEngineObserverList.begin();
        lConst_iterator = mEngineObserverList.end();
        
        for(;lIterator!=lConst_iterator;++lIterator)
        {
            (*lIterator)->Update(this);
        }
    }


    void ai::AIObserver::AddEngineObserver(engine::EngineObserver* rNewobserver){
        mEngineObserverList.push_back(rNewobserver);
        rNewobserver->AddAIObserver(this);
    }




}