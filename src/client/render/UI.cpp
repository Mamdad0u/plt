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
            mText.setFont(mFont);
            mText.setCharacterSize(24);
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


    void render::UI::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform *= getTransform();

        target.draw(mVertices, states);
        target.draw(mText);
    }

}






