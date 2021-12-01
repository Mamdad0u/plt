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
          

            mMenuAction1.setFont(mFont);
            mMenuAction1.setCharacterSize(20);
            mMenuAction1.setPosition(sf::Vector2f(35.f,510.f));
            mRectAction1.setPosition(sf::Vector2f(35.f,510.f));

            mMenuAction3.setFont(mFont);
            mMenuAction3.setCharacterSize(20);
            mMenuAction3.setPosition(sf::Vector2f(180.f,510.f));
            

            mMenuAction4.setFont(mFont);
            mMenuAction4.setCharacterSize(20);
            mMenuAction4.setPosition(sf::Vector2f(180.f,550.f));
           
            
            
        }

    }


    void render::UI::CreateWindow(int rX, int rY, int rWidth, int rHeight){
        mVertices.setPrimitiveType(sf::Quads);
        mVertices.resize(rWidth * rHeight * 4);

        sf::Vertex* lQuad = &mVertices[rWidth*4];


        /* 0 1
           3 2*/
        lQuad[0].position = sf::Vector2f(rX, rY); 
        lQuad[1].position = sf::Vector2f(rX + rWidth, rY);
        lQuad[2].position = sf::Vector2f(rX + rWidth, rY + rHeight);
        lQuad[3].position = sf::Vector2f(rX, rY + rHeight);

        lQuad[0].color = sf::Color(0,0,100,50);
        lQuad[1].color = sf::Color(0,0,100,50);
        lQuad[2].color = sf::Color::Blue;
        lQuad[3].color = sf::Color::Blue;

        
        
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
        mRectAction1.setSize(sf::Vector2f(85,25));
        mRectAction1.setFillColor(sf::Color::Transparent);
        mRectAction1.setOutlineThickness(2);
        mRectAction1.setOutlineColor(sf::Color::Red);

    }

    void render::UI::DEBUG_SetTextAction2(std::string rTextAction) {

        mMenuAction2.setString(rTextAction);
        
       
    }

    void render::UI::DEBUG_SetTextAction3(std::string rTextAction) {

        mMenuAction3.setString(rTextAction);
        
       
    }

    void render::UI::DEBUG_SetTextAction4(std::string rTextAction) {

        mMenuAction4.setString(rTextAction);

    }

    

    void render::UI::MoveUI(){
        mTextVersion.move(sf::Vector2f(1.f,0.f));
        mDebugTextState.move(sf::Vector2f(1.f,0.f));
        mMenuAction1.move(sf::Vector2f(1.f,0.f));
        mMenuAction2.move(sf::Vector2f(1.f,0.f));
        mMenuAction3.move(sf::Vector2f(1.f,0.f));
        mMenuAction4.move(sf::Vector2f(1.f,0.f));

    }


    void render::UI::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform *= getTransform();

        target.draw(mVertices, states);
        target.draw(mTextVersion);
        target.draw(mDebugTextState);
        target.draw(mMenuAction1);
        target.draw(mMenuAction2);
        target.draw(mMenuAction3);
        target.draw(mMenuAction4);
        target.draw(mRectAction1);

    }

}






