#include <render/UI.h>  // Included from library shared_static
#include "UI.h"
#include <iostream>


using namespace std;

namespace render {

    render::UI::UI(){
        
        if (!mFont.loadFromFile("res/font.ttf"))
        {
            cout << "ERROR : Failed to policy " << endl;
        }

        else{
            mTextVersion.setFont(mFont);
            mTextVersion.setCharacterSize(16);
            mTextVersion.setPosition(0,0);

            mDebugTextState.setFont(mFont);
            mDebugTextState.setCharacterSize(24);
            mDebugTextState.setPosition(sf::Vector2f(400.f,0.f));

            mMenuAction2.setFont(mFont);
            mMenuAction2.setCharacterSize(20);
            mMenuAction2.setPosition(sf::Vector2f(35.f,550.f));
            mRectAction2.setPosition(sf::Vector2f(35.f,550.f));
          

            mMenuAction1.setFont(mFont);
            mMenuAction1.setCharacterSize(20);
            mMenuAction1.setPosition(sf::Vector2f(35.f,510.f));
            mRectAction1.setPosition(sf::Vector2f(35.f,510.f));

            mMenuAction3.setFont(mFont);
            mMenuAction3.setCharacterSize(20);
            mMenuAction3.setPosition(sf::Vector2f(180.f,510.f));
            mRectAction3.setPosition(sf::Vector2f(180.f,510.f));
            

            mMenuAction4.setFont(mFont);
            mMenuAction4.setCharacterSize(20);
            mMenuAction4.setPosition(sf::Vector2f(180.f,550.f));
            mRectAction4.setPosition(sf::Vector2f(180.f,550.f));

            mRectLifePointsP1.setPosition(sf::Vector2f(450.f,580.f));
            mRectLifePointsP1.setOutlineThickness(2);
            mRectLifePointsP1.setOutlineColor(sf::Color::White);
            mRectLifePointsP1.setFillColor(sf::Color::Green);
           
            mRectLifePointsP2.setPosition(sf::Vector2f(600.f,580.f));
            mRectLifePointsP2.setOutlineThickness(2);
            mRectLifePointsP2.setOutlineColor(sf::Color::White);
            mRectLifePointsP2.setFillColor(sf::Color::Green);

            mRectLifePointsP3.setPosition(sf::Vector2f(450.f,530.f));
            mRectLifePointsP3.setOutlineThickness(2);
            mRectLifePointsP3.setOutlineColor(sf::Color::White);
            mRectLifePointsP3.setFillColor(sf::Color::Green);

            mRectLifePointsP4.setPosition(sf::Vector2f(600.f,530.f));
            mRectLifePointsP4.setOutlineThickness(2);
            mRectLifePointsP4.setOutlineColor(sf::Color::White);
            mRectLifePointsP4.setFillColor(sf::Color::Green);

            mRectLifePointsP1.setSize(sf::Vector2f(100,15));
            mRectLifePointsP2.setSize(sf::Vector2f(100,15));
            mRectLifePointsP3.setSize(sf::Vector2f(100,15));
            mRectLifePointsP4.setSize(sf::Vector2f(100,15));

            mRectMenu.setPosition(sf::Vector2f(0.f,500.f));
            mRectMenu.setFillColor(sf::Color::Blue);
            mRectMenu.setSize(sf::Vector2f(800,100));

            
            
        }

    }


    void render::UI::CreateWindow(int rX, int rY, int rWidth, int rHeight){
        mVertices.setPrimitiveType(sf::Quads);
        mVertices.resize(rWidth * rHeight * 4);

        mQuad = &mVertices[rWidth*4];


        /* 0 1
           3 2*/
        mQuad[0].position = sf::Vector2f(rX, rY); 
        mQuad[1].position = sf::Vector2f(rX + rWidth, rY);
        mQuad[2].position = sf::Vector2f(rX + rWidth, rY + rHeight);
        mQuad[3].position = sf::Vector2f(rX, rY + rHeight);

        mQuad[0].color = sf::Color(0,0,100,50);
        mQuad[1].color = sf::Color(0,0,100,50);
        mQuad[2].color = sf::Color::Blue;
        mQuad[3].color = sf::Color::Blue;

        
        
    }


    void render::UI::AddTextWindow(const std::string& rText, int rX, int rY){
        mText.setString(rText);
        mText.setPosition(sf::Vector2f((float)rX,(float)rY));
        
    }

    void render::UI::SetTextVersion(string rTextVersion){
        rTextVersion = "ENSEAi " + rTextVersion;
        mTextVersion.setString(rTextVersion);

    }

    void render::UI::DEBUG_SetTextCombatState(std::string rTextState){
        mDebugTextState.setString(rTextState);
        mDebugTextState.setPosition(sf::Vector2f(mDebugTextState.getPosition().x,mDebugTextState.getPosition().y));
    }

    void render::UI::DEBUG_SetTextAction1(std::string rTextAction){

        mMenuAction1.setString(rTextAction);
        mRectAction1.setSize(sf::Vector2f(90,25));
        mRectAction1.setFillColor(sf::Color::Transparent);
        mRectAction1.setOutlineThickness(2);
        mRectAction1.setOutlineColor(sf::Color::Red);

    }

    void render::UI::DEBUG_SetTextAction2(std::string rTextAction) {

        mMenuAction2.setString(rTextAction);
        mRectAction2.setSize(sf::Vector2f(90,25));
        mRectAction2.setFillColor(sf::Color::Transparent);
        mRectAction2.setOutlineThickness(2);
        mRectAction2.setOutlineColor(sf::Color::Red);
        
       
    }

    void render::UI::DEBUG_SetTextAction3(std::string rTextAction) {

        mMenuAction3.setString(rTextAction);
        mRectAction3.setSize(sf::Vector2f(85,25));
        mRectAction3.setFillColor(sf::Color::Transparent);
        mRectAction3.setOutlineThickness(2);
        mRectAction3.setOutlineColor(sf::Color::Red);
        
       
    }

    void render::UI::DEBUG_SetTextAction4(std::string rTextAction) {

        mMenuAction4.setString(rTextAction);
        mRectAction4.setSize(sf::Vector2f(85,25));
        mRectAction4.setFillColor(sf::Color::Transparent);
        mRectAction4.setOutlineThickness(2);
        mRectAction4.setOutlineColor(sf::Color::Red);

    }

    void render::UI::DEBUG_SetLifePoints() {

        

    }

    void render::UI::AskNewGame() {

        mGameOverMenu.setSize(sf::Vector2f(450,500));
        mGameOverMenu.setPosition(sf::Vector2f(250.f,300.f));
        mGameOverMenu.setFillColor(sf::Color::Black);

        mExit.setSize(sf::Vector2f(50,25));
        mExit.setPosition(sf::Vector2f(300.f,350.f));
        mExit.setFillColor(sf::Color::Red);

        mTryAgain.setSize(sf::Vector2f(50,25));
        mTryAgain.setPosition(sf::Vector2f(400.f,350.f));
        mTryAgain.setFillColor(sf::Color::Green);

    }



    

    void render::UI::MoveUI(){
        mTextVersion.move(sf::Vector2f(1.f,0.f));
        mDebugTextState.move(sf::Vector2f(1.f,0.f));
        mMenuAction1.move(sf::Vector2f(1.f,0.f));
        mMenuAction2.move(sf::Vector2f(1.f,0.f));
        mMenuAction3.move(sf::Vector2f(1.f,0.f));
        mMenuAction4.move(sf::Vector2f(1.f,0.f));
        mRectLifePointsP1.move(sf::Vector2f(1.f,0.f));
        mRectLifePointsP2.move(sf::Vector2f(1.f,0.f));
        mRectLifePointsP3.move(sf::Vector2f(1.f,0.f));
        mRectLifePointsP4.move(sf::Vector2f(1.f,0.f));
        mRectAction1.move(sf::Vector2f(1.f,0.f));
        mRectAction2.move(sf::Vector2f(1.f,0.f));
        mRectAction3.move(sf::Vector2f(1.f,0.f));
        mRectAction4.move(sf::Vector2f(1.f,0.f));
        mRectMenu.move(sf::Vector2f(1.f,0.f));
       
    }


    void render::UI::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform *= getTransform();

        target.draw(mVertices, states);
        target.draw(mTextVersion);
        target.draw(mDebugTextState);
        target.draw(mRectMenu);
        target.draw(mMenuAction1);
        target.draw(mMenuAction2);
        target.draw(mMenuAction3);
        target.draw(mMenuAction4);
        target.draw(mRectAction1);
        target.draw(mRectAction2);
        target.draw(mRectAction3);
        target.draw(mRectAction4);
        target.draw(mRectLifePointsP1);
        target.draw(mRectLifePointsP2);
        target.draw(mRectLifePointsP3);
        target.draw(mRectLifePointsP4);
        

    }

}






