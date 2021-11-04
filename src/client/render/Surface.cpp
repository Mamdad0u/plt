#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {

    // NOUVELLE VERSION

    int render::Surface::LoadSurface(const std::string& rTextureName, float rX, float rY, float rWidth, float rHeight){
        string lResPath = "res/" + rTextureName;

        if (!mTexture.loadFromFile(lResPath))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            mQuad.setPrimitiveType(sf::Quads); // Setting interpretation of primitive as quads 
            mQuad.resize(rWidth * rHeight * 4);

            mQuad[0].position = sf::Vector2f(rX, rY);
            mQuad[1].position = sf::Vector2f(rX + rWidth, rX);
            mQuad[2].position = sf::Vector2f(rX + rWidth, rY + rHeight);
            mQuad[3].position = sf::Vector2f(rX, rY + rHeight);
            
            
            mQuad[0].texCoords = sf::Vector2f(rX, rY);
            mQuad[1].texCoords = sf::Vector2f(rX + rWidth, rX);
            mQuad[2].texCoords = sf::Vector2f(rX + rWidth, rY + rHeight);
            mQuad[3].texCoords = sf::Vector2f(rX, rY + rHeight);
        }

        return 0;
    }


    void render::Surface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &mTexture;

        // et on dessine enfin le tableau de vertex
        target.draw(mQuad, states);
        

    }







    // ANCIENNE VERSION DU RENDU 
    /* render::Surface::Surface(){
        mView.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    }


    

    int render::Surface::LoadTexture(std::string rTextureName, int rX, int rY, int rWidth, int rHeight){

        string lResPath = "res/" + rTextureName;

        if (!mTexture.loadFromFile(lResPath,sf::IntRect(rX, rY, rWidth, rHeight)))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            mSprite.setTexture(mTexture);
        }

        return 0;

    }




    void render::Surface::ChangeViewArena(sf::RenderWindow& rWindow){
        rWindow.setView(mView);
        mView.move(sf::Vector2f(1.f,0.f));

    } */




}

