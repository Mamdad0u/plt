#include <render/RenderObserver.h>  // Included from library shared_static
#include "RenderObserver.h"
#include <iostream>

using namespace std;

namespace render {


    void render::RenderObserver::AddEngineObserver(client::EngineObserver* rNewObserver) {

        mEngineObserverList.push_back(rNewObserver);
        rNewObserver->AddRenderObserver(this);
    }

    void render::RenderObserver::NotifyEndRendering() {

        std::list<client::EngineObserver*>::iterator lIterator; 
        std::list<client::EngineObserver*>::const_iterator lConst_iterator;

        lIterator = mEngineObserverList.begin();
        lConst_iterator = mEngineObserverList.end();
        
        for(;lIterator!=lConst_iterator;++lIterator)
        {
            (*lIterator)->Update(this);
        }

    }
}