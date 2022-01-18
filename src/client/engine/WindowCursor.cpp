#include <engine/WindowCursor.h>  // Included from library shared_static
#include "WindowCursor.h"
#include <iostream>

using namespace std;

namespace engine {
    engine::WindowCursor::WindowCursor(){
        mX=0;
        mY=0;
    }

    void engine::WindowCursor::GetPositionCursor(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;
    }

    bool engine::WindowCursor::Click(sf::RenderWindow& rWindow){
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

    bool engine::WindowCursor::ClickAction1(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<125)&&(mX>35)&&(mY<535)&&(mY>510)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }

    bool engine::WindowCursor::ClickAction2(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<125)&&(mX>35)&&(mY<575)&&(mY>550)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }

    bool engine::WindowCursor::ClickAction3(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<265)&&(mX>180)&&(mY<535)&&(mY>510)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }
    bool engine::WindowCursor::ClickAction4(sf::RenderWindow& rWindow){
        sf::Vector2i lLocalPosition;
        lLocalPosition= sf::Mouse::getPosition(rWindow);
        mX=lLocalPosition.x;
        mY=lLocalPosition.y;

        if((mX<265)&&(mX>180)&&(mY<575)&&(mY>550)){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
        
        return false;
        
    }



}