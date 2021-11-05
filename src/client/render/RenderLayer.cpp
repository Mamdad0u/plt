#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {
    
    int render::RenderLayer::LoadBackground(){
        if(mBackgroundSurface.LoadSurface("Arena_1.png", 0, 0, 3200, 600)){
            cout << "ERROR : Failed to load Background " << endl;
            return -1;
        }
        
        return 0;
    }

    int render::RenderLayer::LoadCharacters(int rCharacterSelected){
        
        switch(rCharacterSelected){
            case 0:
                
                break;




        }

    }


    void render::RenderLayer::draw(sf::RenderWindow& rWindow){
        rWindow.draw(mBackgroundSurface);

    }

}

