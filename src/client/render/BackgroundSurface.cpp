#include <render/BackgroundSurface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {

    render::BackgroundSurface::BackgroundSurface(){
        
        mView.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    }
    
    int render::BackgroundSurface::LoadBackgroundSprite(const std::string& rTextureName){
        string lResPath = "res/" + rTextureName;

        if (!mTexture.loadFromFile(lResPath))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            cout << "Loading sprite " << rTextureName << endl;
            mSprite.setTexture(mTexture);
           
        }


        return 0;
    }

    void render::BackgroundSurface::MoveBackgroundView(sf::RenderWindow& rWindow, int rMovingProgress){
        rWindow.setView(mView);
        mView.move(sf::Vector2f(1.f,0.f));
        
    }

    void render::BackgroundSurface::ResetViewPosition(){
        mView.setCenter(sf::Vector2f(0,0));
    }



    int render::BackgroundSurface::LoadShape(const std::string& rTextureName, float rX, float rY){
        string lResPath = "res/" + rTextureName;
        sf::Vector2f lTextureSize;

        if (!mTexture.loadFromFile(lResPath))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            lTextureSize = (sf::Vector2f)mTexture.getSize();
            mQuad.setPrimitiveType(sf::Quads); // Setting interpretation of primitive as quads 
            mQuad.resize(lTextureSize.x * lTextureSize.y * 4);

            //mQuad[0].position = (sf::Vector2f)mTexture.getSize();

            mQuad[0].position = sf::Vector2f(rX, rY); 
            mQuad[1].position = sf::Vector2f(rX + lTextureSize.x, rY);
            mQuad[2].position = sf::Vector2f(rX + lTextureSize.x, rY + lTextureSize.y);
            mQuad[3].position = sf::Vector2f(rX, rY + lTextureSize.y);
            
            
            mQuad[0].texCoords = sf::Vector2f(rX, rY);
            mQuad[1].texCoords = sf::Vector2f(rX + lTextureSize.x, rY);
            mQuad[2].texCoords = sf::Vector2f(rX + lTextureSize.x, rY + lTextureSize.y);
            mQuad[3].texCoords = sf::Vector2f(rX, rY + lTextureSize.y);
        }

        return 0;
    }

    void render::BackgroundSurface::DrawBackground(sf::RenderWindow& rWindow){
        rWindow.draw(mSprite);
    }
}
