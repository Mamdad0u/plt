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

        

    }
}