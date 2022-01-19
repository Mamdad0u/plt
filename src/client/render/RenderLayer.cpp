#include <render/RenderLayer.h>  // Included from library shared_static
#include "RenderLayer.h"
#include <iostream>

using namespace std;

namespace render {


    render::RenderLayer::RenderLayer(){
        CharacterSurface* lInit_SpritePlayerCharacter;
        mPlayerCharactersSurface.reserve(4);
        mArenaEnemySurface.reserve(10);
        mBackgroundSurface = new BackgroundSurface;

        for(int i=0;i<5;i++){
            lInit_SpritePlayerCharacter = new CharacterSurface;
            mPlayerCharactersSurface.push_back(*(lInit_SpritePlayerCharacter));
        }
    }

    render::RenderLayer::RenderLayer(engine::EngineObserver* rNewObserver){
        CharacterSurface* lInit_SpritePlayerCharacter;
        mPlayerCharactersSurface.reserve(5);
        mArenaEnemySurface.reserve(10);
        AddEngineObserver(rNewObserver);
        mBackgroundSurface = new BackgroundSurface;
        
        for(int i=0;i<5;i++){
            lInit_SpritePlayerCharacter = new CharacterSurface;
            mPlayerCharactersSurface.push_back(*(lInit_SpritePlayerCharacter));
        }
    }
    
    int render::RenderLayer::LoadBackground(int lArenaNumber){

        string lArenaPath = "backgrounds/Arena" + to_string(lArenaNumber);
        lArenaPath = lArenaPath + ".png";

        if(mBackgroundSurface->LoadBackgroundSprite(lArenaPath)){
            cout << "ERROR : Failed to load background " << endl;
            return -1;
        }
        mBackgroundSurface->SetRender(true);
        return 0;
    }

    int render::RenderLayer::LoadEnemy(int rEnemySelected,int rX, int rY, int rSide){
        CharacterSurface lEnemytoAdd;
        int lLastEnemyPosition=mArenaEnemySurface.size();
        string lEnemyString = "sprites/Character" + to_string(rEnemySelected);
        
        lEnemyString = lEnemyString +".png";
        mArenaEnemySurface.push_back(*(new CharacterSurface));

        if(mArenaEnemySurface[lLastEnemyPosition].LoadCharacterSprite(lEnemyString, rX, rY, rSide)){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }
        mArenaEnemySurface[lLastEnemyPosition].SetCharacterAnimation(0);
        mArenaEnemySurface[lLastEnemyPosition].SetRender(true);
        return 0;

    }

    int render::RenderLayer::LoadCharacter(int rCharacterPosition, int rSpriteCharacter, int rX, int rY, int rSide){
        rCharacterPosition--;
        CharacterSurface* lCharactertoAdd = new CharacterSurface;
        int lLastCharacterPosition = mPlayerCharactersSurface.size();
        string lCharacterString = "sprites/Character" + to_string(rSpriteCharacter);
        
        lCharacterString = lCharacterString + ".png";

        
        
       // mPlayerCharactersSurface.push_back(*(new Surface));
        
        if(mPlayerCharactersSurface[rCharacterPosition].LoadCharacterSprite(lCharacterString, rX, rY, rSide)== -1){
            cout << "ERROR : Failed to load character " << endl;
            return -1;
        }

    //    mPlayerCharactersSurface.push_back(*(lCharactertoAdd));

        mPlayerCharactersSurface[rCharacterPosition].SetCharacterAnimation(0);
        mPlayerCharactersSurface[rCharacterPosition].SetRender(true);
        


       

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
             * Le ème est pour le charactere enemy
             * 
             */
        case 1:
            LoadCharacter(1, rSpriteNumber,250,250,1);
            mPlayerCharacterTeamSize++;
            break;
        
        case 2:
            LoadCharacter(2, rSpriteNumber,200,300,1);
            mPlayerCharacterTeamSize++;
            break;

        case 3:
            LoadCharacter(3, rSpriteNumber,150,350,1);
            mPlayerCharacterTeamSize++;
            break;

        case 4:
            LoadCharacter(4, rSpriteNumber,100,400,1);
            mPlayerCharacterTeamSize++;
            break;

        case 5:
            LoadEnemy(rSpriteNumber,600,325,0);
            break;
        }


        
    }

    void render::RenderLayer::RefreshLifePoints(std::vector<state::Character> rPlayersCharacters) {

        float LPratios[4] = {0,0,0,0};

        for (size_t k = 0; k < rPlayersCharacters.size(); k++)
        {
            LPratios[k] = ((float)rPlayersCharacters[k].GetCharacterStats(state::LIFE_POINTS)/(float)rPlayersCharacters[k].GetCharacterStats(state::MAX_LIFE_POINTS))*100;
        }
        
        mUI.mRectLifePointsP1.setSize(sf::Vector2f(LPratios[0],25));
        mUI.mRectLifePointsP2.setSize(sf::Vector2f(LPratios[1],25));
        mUI.mRectLifePointsP3.setSize(sf::Vector2f(LPratios[2],25));
        mUI.mRectLifePointsP4.setSize(sf::Vector2f(LPratios[3],25));
        //mUI.mRectLifePointsP1.setFillColor(sf::Color::Yellow);
        

    }


    void render::RenderLayer::LoadUI(){

        
        mUI.CreateWindow(0,500,800,100);
        mUI.SetTextVersion("Release 4.1");
        mUI.DEBUG_SetTextAction1("Attack 1");
        mUI.DEBUG_SetTextAction2("Attack 2");
        mUI.DEBUG_SetTextAction3("Spell 1");
        mUI.DEBUG_SetTextAction4("Spell 2");
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

            case state::GAME_OVER:
                mUI.DEBUG_SetTextCombatState("GAME_OVER");

                mUI.AskNewGame();
                


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


        mBackgroundSurface->MoveBackgroundView(rWindow, mMovingProgress);
        
        mUI.MoveUI();
      
        mMovingProgress++;
        return (mMovingProgress-1);
    }
    
    void render::RenderLayer::GoNextArena(){
        for(int i=0;i<mPlayerCharacterTeamSize;i++){
            mPlayerCharactersSurface[i].ResetPosition(i);
        }
        mBackgroundSurface->ResetViewPosition();
        mUI.ResetUIPositon();
        
    }

    void render::RenderLayer::UnloadPlayerSpriteCharacter(int rCharacterIndex){
        mPlayerCharactersSurface[rCharacterIndex].SetRender(false);
        mPlayerCharacterTeamSize--;

    }

    void render::RenderLayer::draw(sf::RenderWindow& rWindow, int rEnemyIndex, state::CombatStatus rGameStatus){
        mBackgroundSurface->DrawSurface(rWindow);

        if(rGameStatus==state::IN_COMBAT){
            
            
            mArenaEnemySurface[rEnemyIndex].DrawSurface(rWindow);
        }
        
        rWindow.draw(mUI);
        for(int i=0;i<4;i++){
            mPlayerCharactersSurface[i].DrawSurface(rWindow);
            

        }

        
    }
    

}

