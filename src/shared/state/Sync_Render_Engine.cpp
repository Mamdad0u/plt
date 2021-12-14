#include "Sync_Render_Engine.h"

using namespace std;

namespace state {

    state::Sync_Render_Engine::Sync_Render_Engine (state::State rCurrentSate, render::RenderLayer rCurrentLayer, client::Engine rEngine) {

        mEngine = rEngine;
        mCurrentLayer = rCurrentLayer;
        mCurrentState = rCurrentSate;

    }

}