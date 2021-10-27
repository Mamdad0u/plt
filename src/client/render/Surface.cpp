#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {
    render::Surface::Surface(){
        view.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    }




    int render::Surface::LoadTexture(std::string rTextureName){

        string lResPath = "res/" + rTextureName;

        if (!texture.loadFromFile(lResPath,sf::IntRect(0, 0, 1400, 1050)))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        else{
            sprite.setTexture(texture);
            sprite.setScale(sf::Vector2f(0.8f,0.6f));

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

