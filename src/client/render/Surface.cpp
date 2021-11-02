#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {
    render::Surface::Surface(){
        view.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    }




    int render::Surface::LoadTexture(std::string rTextureName, int rX, int rY, int rWidth, int rHeight){

        string lResPath = "res/" + rTextureName;

        if (!texture.loadFromFile(lResPath,sf::IntRect(rX, rY, rWidth, rHeight)))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            sprite.setTexture(texture);
        }

        return 0;

    }

    void render::Surface::Draw(sf::RenderWindow& rWindow){
        rWindow.draw(sprite);

    }

    void render::Surface::TestTransform(){

        
    }

    void render::Surface::TestView(sf::RenderWindow& rWindow){
        rWindow.setView(view);
        //view.setRotation(20.f);
        view.move(sf::Vector2f(1.f,0.f));
    }
}

