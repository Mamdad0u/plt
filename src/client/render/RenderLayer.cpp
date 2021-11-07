#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {
    
    int render::RenderLayer::LoadBackground(){
        if(mBackgroundSurface.LoadBackgroundSprite("Arena_1.png")){
            cout << "ERROR : Failed to load background " << endl;
            return -1;
        }
        
        return 0;
    }

    int render::RenderLayer::LoadCharacters(int rCharacterSelected, int rX, int rY){
        
        if(mCharactersSurface.LoadCharacterSprite("Character1.png", rX, rY)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }

        return 0;
    }


    void render::RenderLayer::AnimateCharacters(){
        mCharactersSurface.ChangeCharacterAnimation(0);

    }





    

    void render::RenderLayer::draw(sf::RenderWindow& rWindow){
        mBackgroundSurface.draw(rWindow);
        mCharactersSurface.draw(rWindow);
    }

}

