#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {


    render::RenderLayer::RenderLayer(){
        mPlayerCharactersSurface.reserve(4);
        mArenaEnemySurface.reserve(4);

    }

    render::RenderLayer::RenderLayer(client::EngineObserver* rNewObserver){
        mPlayerCharactersSurface.reserve(4);
        mArenaEnemySurface.reserve(4);
        AddEngineObserver(rNewObserver);
    }
    
    int render::RenderLayer::LoadBackground(int lArenaNumber){

        string lArenaPath = "backgrounds/Arena" + to_string(lArenaNumber);
        lArenaPath = lArenaPath + ".png";

        if(mBackgroundSurface.LoadBackgroundSprite(lArenaPath)){
            cout << "ERROR : Failed to load background " << endl;
            return -1;
        }
        
        return 0;
    }

    int render::RenderLayer::LoadEnemy(int rEnemySelected,int rX, int rY, int rSide){
        Surface lEnemytoAdd;
        int lLastEnemyPosition=mArenaEnemySurface.size();
        string lEnemyString = "sprites/Character" + to_string(rEnemySelected);
        
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
        string lCharacterString = "sprites/Character" + to_string(rCharacterSelected);
        
        lCharacterString = lCharacterString + ".png";


        
        mPlayerCharactersSurface.push_back(*(new Surface));
        
        if(mPlayerCharactersSurface[lLastCharacterPosition].LoadCharacterSprite(lCharacterString, rX, rY, rSide)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }



        mPlayerCharactersSurface[lLastCharacterPosition].SetCharacterAnimation(0);
        
        
       

        return 0;
    }

    void render::RenderLayer::UpdateCharacterOnScreen(int rSpriteNumber, int rPositionOnScreen){
/*         lRender.LoadCharacter(1,250,250,1);
        lRender.LoadCharacter(2,200,300,1);
        lRender.LoadCharacter(5,150,350,1);
        lRender.LoadCharacter(7,100,400,1); */
        
        
        switch (rPositionOnScreen)
        {

            /**
             * @brief Les case {0..3} concernent les charactères du joueur
             * Le 4ème est pour le charactere enemy
             * 
             */
        case 0:
            LoadCharacter(rSpriteNumber,250,250,1);
            break;
        
        case 1:
            LoadCharacter(rSpriteNumber,200,300,1);
            break;

        case 2:
            LoadCharacter(rSpriteNumber,150,350,1);
            break;

        case 3:
            LoadCharacter(rSpriteNumber,100,400,1);
            break;

        case 4:
            LoadEnemy(rSpriteNumber,600,325,0);
            break;
        }

        
    }

    void render::RenderLayer::LoadUI(){
        
        mUI.CreateWindow(0,500,800,100);
        mUI.SetTextVersion("BUILD_VERSION_2.3");
        mUI.DEBUG_SetTextAction1("Attack/Spell");
        mUI.DEBUG_SetTextAction2("Objets");
        mUI.DEBUG_SetTextAction3("Menu");
        mUI.DEBUG_SetTextAction4("Quitter le jeu");
        mUI.DEBUG_SetLifePoints();
        

    }

    



    void render::RenderLayer::DEBUG_SetRenderState(state::CombatStatus rNewState){
        switch(rNewState){
            case state::IN_COMBAT:
                mUI.DEBUG_SetTextCombatState("IN_COMBAT");

                break;

            case state::OUT_COMBAT:
                mUI.DEBUG_SetTextCombatState("OUT_COMBAT");
                break;

            case state::RENDER_PROCESSING:
                mUI.DEBUG_SetTextCombatState("RENDER_PROCESSING");
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
                // cout << "L'animation devient statique" << endl;
                mPlayerCharactersSurface[i].SetCharacterAnimation(0);
                NotifyEndRendering();
                
            }

            mPlayerCharactersSurface[i].MoveCharacterSprite();
            mArenaEnemySurface[i].MoveCharacterSprite();
        }


        mBackgroundSurface.MoveBackgroundView(rWindow, mMovingProgress);
        
        mUI.MoveUI();
      
        mMovingProgress++;
        return (mMovingProgress-1);
    }

    void render::RenderLayer::draw(sf::RenderWindow& rWindow, int rEnemyIndex, state::CombatStatus rGameStatus){
        mBackgroundSurface.DrawSprite(rWindow);

        if(rGameStatus==state::IN_COMBAT){
            
            
            mArenaEnemySurface[rEnemyIndex].DrawSprite(rWindow);
        }
        
        rWindow.draw(mUI);
        for(int i=0;i<mPlayerCharactersSurface.size();i++){
            
            mPlayerCharactersSurface[i].DrawSprite(rWindow);


        }

        
    }

    

}

