#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {


    render::RenderLayer::RenderLayer(){
        mManyCharactersSurface.reserve(4);

    }
    
    int render::RenderLayer::LoadBackground(){
        if(mBackgroundSurface.LoadBackgroundSprite("Arena_1.png")){
            cout << "ERROR : Failed to load background " << endl;
            return -1;
        }
        
        return 0;
    }

    int render::RenderLayer::LoadCharacters(int rCharacterSelected, int rX, int rY){
        string lCharacterString = "Character" + to_string(rCharacterSelected);
        lCharacterString = lCharacterString + ".png";

        if(mCharactersSurface.LoadCharacterSprite(lCharacterString, rX, rY)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }

        mCharactersSurface.SetCharacterAnimation(1);
        return 0;
    }

    int render::RenderLayer::LoadManyCharacters(int rCharacterSelected, int rX, int rY){
        Surface lCharactertoAdd;
        int lLastCharacterPosition = mManyCharactersSurface.size();
        string lCharacterString = "Character" + to_string(rCharacterSelected);
        
        lCharacterString = lCharacterString + ".png";


        
        mManyCharactersSurface.push_back(*(new Surface));
        
        if(mManyCharactersSurface[lLastCharacterPosition].LoadCharacterSprite(lCharacterString, rX, rY)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }



        mManyCharactersSurface[lLastCharacterPosition].SetCharacterAnimation(1);
        
        
       

        return 0;
    }


    void render::RenderLayer::AnimateCharacters(){
        int lLastCharacterPosition = mManyCharactersSurface.size();

        for(int i=0;i<lLastCharacterPosition;i++){
            mManyCharactersSurface[i].UpdateCharacterAnimation();
        }


        //mCharactersSurface.UpdateCharacterAnimation();

    }

    int render::RenderLayer::GoNextCombat(sf::RenderWindow& rWindow){
        int lLastCharacterPosition = mManyCharactersSurface.size();


        for(int i=0;i<lLastCharacterPosition;i++){
            if(mMovingProgress == 0){
                mManyCharactersSurface[i].SetCharacterAnimation(1);
            }
            else if(mMovingProgress == 799){
                mManyCharactersSurface[i].SetCharacterAnimation(0);
            }

            mManyCharactersSurface[i].MoveCharacterSprite();
        }


        mBackgroundSurface.MoveBackgroundView(rWindow);
        
        
        mMovingProgress++;
        return mMovingProgress;
    }

    void render::RenderLayer::draw(sf::RenderWindow& rWindow){
        mBackgroundSurface.draw(rWindow);
      //  mCharactersSurface.draw(rWindow);

        

        for(int i=0;i<mManyCharactersSurface.size();i++){
            
            mManyCharactersSurface[i].draw(rWindow);


        }
    }
    

}

