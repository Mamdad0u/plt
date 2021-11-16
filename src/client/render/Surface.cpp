#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {

    // NOUVELLE VERSION

    render::Surface::Surface(){
        mView.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    }

    int render::Surface::LoadShape(const std::string& rTextureName, float rX, float rY){
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

    int render::Surface::LoadCharacterSprite(const std::string& rTextureName, int rX, int rY){

        string lResPath = "res/" + rTextureName;
        mCharacterRectSource.left = 0;
        mCharacterRectSource.top = 0;
        mCharacterRectSource.width = 16;
        mCharacterRectSource.height = 24;

        
        if (!mTexture.loadFromFile(lResPath))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            cout << "Loading sprite " << rTextureName << endl;
            mSprite.setTexture(mTexture);
            mSprite.setTextureRect(mCharacterRectSource);
            
            mSprite.move((sf::Vector2f)sf::Vector2u(rX, rY));
            mSprite.scale(sf::Vector2f(2.5f,2.5f));
        }

        return 0;

    }

    int render::Surface::LoadBackgroundSprite(const std::string& rTextureName){
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

    void render::Surface::SetCharacterAnimation(int rNewAnimation){
        
        switch(rNewAnimation){
            case 0:
                mCharacterRectSource.top = 0;
                break;

            case 1:
                mCharacterRectSource.top = 32;
                break;
        }
        
    }

    void render::Surface::UpdateCharacterAnimation(){
        mCharacterRectSource.left += 16;


        if(mCharacterRectSource.left == 96){
            mCharacterRectSource.left = 0;
        }

        mSprite.setTextureRect(mCharacterRectSource);

    }

    void render::Surface::MoveBackgroundView(sf::RenderWindow& rWindow){
        rWindow.setView(mView);
        mView.move(sf::Vector2f(1.f,0.f));
    }

    void render::Surface::MoveCharacterSprite(){
        mSprite.move(1.f, 0.f);

    }

    void render::Surface::DrawSprite(sf::RenderWindow& rWindow){
        rWindow.draw(mSprite);
    }








}

