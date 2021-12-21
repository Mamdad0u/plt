#include <client/WindowCursor.h>  // Included from library shared_static
#include "WindowCursor.h"
#include <iostream>

using namespace std;

namespace client {
    client::WindowCursor::WindowCursor(){
        mX=0;
        mY=0;
    }

    void client::WindowCursor::GetPositionCursor(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;
    }

    bool client::WindowCursor::Click(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<800)&&(mX>0)&&(mY<600)&&(mY>500)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }

    bool client::WindowCursor::ClickAction1(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<165)&&(mX>35)&&(mY<535)&&(mY>510)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }

    bool client::WindowCursor::ClickAction2(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<95)&&(mX>35)&&(mY<575)&&(mY>550)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }

    bool client::WindowCursor::ClickAction3(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<225)&&(mX>180)&&(mY<535)&&(mY>510)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }
    bool client::WindowCursor::ClickAction4(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<335)&&(mX>180)&&(mY<575)&&(mY>550)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }



}