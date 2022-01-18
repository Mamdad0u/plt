#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {

    // NOUVELLE VERSION

    void render::Surface::DrawSurface(sf::RenderWindow& rWindow){
        rWindow.draw(mSprite);
    }

}

