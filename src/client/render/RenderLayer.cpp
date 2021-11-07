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
        
        if(mCharactersSurface.LoadCharacterSprite("Character4.png", rX, rY)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }

        mCharactersSurface.SetCharacterAnimation(1);
        return 0;
    }


    void render::RenderLayer::AnimateCharacters(){
        mCharactersSurface.UpdateCharacterAnimation();

    }

    int render::RenderLayer::GoNextCombat(sf::RenderWindow& rWindow){
        if(mMovingProgress == 0){
            mCharactersSurface.SetCharacterAnimation(1);
        }
        else if(mMovingProgress == 799){
            mCharactersSurface.SetCharacterAnimation(0);
        }

        mBackgroundSurface.MoveBackgroundView(rWindow);
        mCharactersSurface.MoveCharacterSprite();
        
        mMovingProgress++;
        return mMovingProgress;
    }

    void render::RenderLayer::draw(sf::RenderWindow& rWindow){
        mBackgroundSurface.draw(rWindow);
        mCharactersSurface.draw(rWindow);
    }
    

}

