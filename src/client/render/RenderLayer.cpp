#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {


    render::RenderLayer::RenderLayer(){
        mPlayerCharactersSurface.reserve(4);

    }
    
    int render::RenderLayer::LoadBackground(){
        if(mBackgroundSurface.LoadBackgroundSprite("rue_map.png")){
            cout << "ERROR : Failed to load background " << endl;
            return -1;
        }
        
        return 0;
    }


    int render::RenderLayer::LoadCharacter(int rCharacterSelected, int rX, int rY){
        Surface lCharactertoAdd;
        int lLastCharacterPosition = mPlayerCharactersSurface.size();
        string lCharacterString = "Character" + to_string(rCharacterSelected);
        
        lCharacterString = lCharacterString + ".png";


        
        mPlayerCharactersSurface.push_back(*(new Surface));
        
        if(mPlayerCharactersSurface[lLastCharacterPosition].LoadCharacterSprite(lCharacterString, rX, rY)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }



        mPlayerCharactersSurface[lLastCharacterPosition].SetCharacterAnimation(0);
        
        
       

        return 0;
    }

    void render::RenderLayer::LoadUI(){
        
        mUI.CreateWindow(0,500,800,100);
        mUI.SetTextVersion("Release V2.2");
        mUI.DEBUG_SetTextAction1("Action 1");
        mUI.DEBUG_SetTextAction2("Action 2");
        mUI.DEBUG_SetTextAction3("Action 3");
        mUI.DEBUG_SetTextAction4("Action 4");
        

    }



    void render::RenderLayer::DEBUG_SetRenderState(state::CombatStatus rNewState){

        switch(rNewState){
            case state::IN_COMBAT:
                mUI.DEBUG_SetTextCombatState("IN_COMBAT");

                break;

            case state::OUT_COMBAT:
                mUI.DEBUG_SetTextCombatState("OUT_COMBAT");
                break;


        }








    }


    void render::RenderLayer::AnimateCharacters(){
        int lLastCharacterPosition = mPlayerCharactersSurface.size();

        for(int i=0;i<lLastCharacterPosition;i++){
            mPlayerCharactersSurface[i].UpdateCharacterAnimation();
        }


    }

    int render::RenderLayer::GoNextCombat(sf::RenderWindow& rWindow){
        int lLastCharacterPosition = mPlayerCharactersSurface.size();


        for(int i=0;i<lLastCharacterPosition;i++){
            if(mMovingProgress == 0){
                mPlayerCharactersSurface[i].SetCharacterAnimation(1);
            }
            else if(mMovingProgress == 799){
                mPlayerCharactersSurface[i].SetCharacterAnimation(0);
                
            }

            mPlayerCharactersSurface[i].MoveCharacterSprite();
        }


        mBackgroundSurface.MoveBackgroundView(rWindow);
        
        mUI.MoveUI();
        mMovingProgress++;
        return mMovingProgress;
    }

    void render::RenderLayer::draw(sf::RenderWindow& rWindow){
        mBackgroundSurface.DrawSprite(rWindow);
      
        

        for(int i=0;i<mPlayerCharactersSurface.size();i++){
            
            mPlayerCharactersSurface[i].DrawSprite(rWindow);


        }

        rWindow.draw(mUI);
    }
    

}

