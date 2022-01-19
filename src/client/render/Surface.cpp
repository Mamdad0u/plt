#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {

    // NOUVELLE VERSION
    void render::Surface::SetRender(bool rValue){
        mIsRender = rValue;
    }

    void render::Surface::DrawSurface(sf::RenderWindow& rWindow){
        if(mIsRender){
            rWindow.draw(mSprite);
        }
        
    }

}

