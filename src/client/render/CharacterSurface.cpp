#include <render/CharacterSurface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {

    int render::CharacterSurface::LoadCharacterSprite(const std::string& rTextureName, int rX, int rY, int rSide){
        string lResPath = "res/" + rTextureName;
        

        if(rSide==1){ //Si le Character est un personnage du joueur
            //  cout << "Joueur" << endl;
             mCharacterRectSource.left = 0;
             mCharacterRectSource.top = 0;
             mCharacterRectSource.width = 16;
             mCharacterRectSource.height = 24;
        }
        if(rSide==0){ //Si le Character est un boss
            
             mCharacterRectSource.left = 96;
             mCharacterRectSource.top = 0;
             mCharacterRectSource.width = 16;
             mCharacterRectSource.height = 24;
        }
       

        
        if (mTexture.loadFromFile(lResPath) == false)
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
    void render::CharacterSurface::SetCharacterAnimation(int rNewAnimation){
        
        switch(rNewAnimation){
            case 0:
                mCharacterRectSource.top = 0;
                break;

            case 1:
                mCharacterRectSource.top = 32;
                break;
        }
        
    }

    void render::CharacterSurface::UpdateCharacterAnimation(int rSize){
        mCharacterRectSource.left += 16;

        if(rSize==0){
            if(mCharacterRectSource.left == 192){
                mCharacterRectSource.left = 96;
            }
        }
        if(rSize==1){
            if(mCharacterRectSource.left == 96){
                mCharacterRectSource.left = 0;
            }
        }

        mSprite.setTextureRect(mCharacterRectSource);

    }

    void render::CharacterSurface::MoveCharacterSprite(){
        mSprite.move(1.f, 0.f);

    }


    void render::CharacterSurface::ResetPosition(int lCharacterPosition){
        mSprite.setPosition(sf::Vector2f(250 - (lCharacterPosition * 50)  ,250 + (lCharacterPosition * 50))); // reset character position on screen for combat 1 of new arena
    }

    void render::CharacterSurface::DrawCharacter(sf::RenderWindow& rWindow){
        rWindow.draw(mSprite);
    }

}
