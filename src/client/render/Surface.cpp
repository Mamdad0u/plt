#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {
    int render::Surface::LoadTexture(std::string rTextureName){

        string lResPath = "res/" + rTextureName;

        if (!texture.loadFromFile(lResPath,sf::IntRect(100, 100, 500, 500)))
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

        
            sprite.setScale(sf::Vector2f(0.25f, 0.5f));
        
            sprite.rotate(1.f);



    }
}

