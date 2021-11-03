#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {
    render::Surface::Surface(){
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

    void render::Surface::Draw(sf::RenderWindow& rWindow){
        rWindow.draw(mSprite);

    }


    void render::Surface::ChangeViewArena(sf::RenderWindow& rWindow){
        rWindow.setView(mView);
        mView.move(sf::Vector2f(1.f,0.f));

    }




}

