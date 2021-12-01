#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {


    render::RenderLayer::RenderLayer(){
        mPlayerCharactersSurface.reserve(4);
        mArenaEnemySurface.reserve(4);

    }
    
    int render::RenderLayer::LoadBackground(){
        if(mBackgroundSurface.LoadBackgroundSprite("rue_map.png")){
            cout << "ERROR : Failed to load background " << endl;
            return -1;
        }
        
        return 0;
    }

    int render::RenderLayer::LoadEnemy(int rEnemySelected,int rX, int rY, int rSide){
        Surface lEnemytoAdd;
        int lLastEnemyPosition=mArenaEnemySurface.size();
        string lEnemyString = "Character" + to_string(rEnemySelected);
        
        lEnemyString = lEnemyString +".png";
        mArenaEnemySurface.push_back(*(new Surface));

        if(mArenaEnemySurface[lLastEnemyPosition].LoadCharacterSprite(lEnemyString, rX, rY, rSide)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }
        mArenaEnemySurface[lLastEnemyPosition].SetCharacterAnimation(0);

        return 0;

    }

    int render::RenderLayer::LoadCharacter(int rCharacterSelected, int rX, int rY, int rSide){
        Surface lCharactertoAdd;
        int lLastCharacterPosition = mPlayerCharactersSurface.size();
        string lCharacterString = "Character" + to_string(rCharacterSelected);
        
        lCharacterString = lCharacterString + ".png";


        
        mPlayerCharactersSurface.push_back(*(new Surface));
        
        if(mPlayerCharactersSurface[lLastCharacterPosition].LoadCharacterSprite(lCharacterString, rX, rY, rSide)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }



        mPlayerCharactersSurface[lLastCharacterPosition].SetCharacterAnimation(0);
        
        
       

        return 0;
    }

    void render::RenderLayer::LoadUI(){
        
        mUI.CreateWindow(0,500,800,100);
        mUI.SetTextVersion("BUILD_VERSION_2.3");
        mUI.DEBUG_SetTextAction1("Attack/Spell");
        mUI.DEBUG_SetTextAction2("Objets");
        mUI.DEBUG_SetTextAction3("Menu");
        mUI.DEBUG_SetTextAction4("Quitter le jeu");
        

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
        int lLastEnemyPosition = mArenaEnemySurface.size();

        for(int i=0;i<lLastCharacterPosition;i++){
            mPlayerCharactersSurface[i].UpdateCharacterAnimation(1);
        }

        
        for(int j=0;j<lLastEnemyPosition;j++){
            mArenaEnemySurface[j].UpdateCharacterAnimation(0);
        }

    }

    int render::RenderLayer::GoNextCombat(sf::RenderWindow& rWindow){
        int lLastCharacterPosition = mPlayerCharactersSurface.size();


        for(int i=0;i<lLastCharacterPosition;i++){
            if(mMovingProgress%800!=0){
               // cout << "L'animation devient mobile" << endl;
                mPlayerCharactersSurface[i].SetCharacterAnimation(1);
            }
            else if(mMovingProgress%800==0){
                //cout << "L'animation devient statique" << endl;
                mPlayerCharactersSurface[i].SetCharacterAnimation(0);
                
            }

            mPlayerCharactersSurface[i].MoveCharacterSprite();
            mArenaEnemySurface[i].MoveCharacterSprite();
        }


        mBackgroundSurface.MoveBackgroundView(rWindow, mMovingProgress);
        
        mUI.MoveUI();
      
        mMovingProgress++;
        return (mMovingProgress-1);
    }

    void render::RenderLayer::draw(sf::RenderWindow& rWindow, int rEnemyIndex, state::State GameStatus){
        mBackgroundSurface.DrawSprite(rWindow);

        if(GameStatus.GetCombatState()==state::IN_COMBAT){
            mArenaEnemySurface[rEnemyIndex].DrawSprite(rWindow);
        }
        

        for(int i=0;i<mPlayerCharactersSurface.size();i++){
            
            mPlayerCharactersSurface[i].DrawSprite(rWindow);


        }

        rWindow.draw(mUI);
    }
    

}

