#include <render/Surface.h>
#include "Surface.h"
#include <iostream>

using namespace std;

namespace render {
    int render::Surface::LoadTexture(std::string rTextureName){

        string lResPath = "res/" + rTextureName;

        if (!texture.loadFromFile(lResPath,sf::IntRect(10, 10, 32, 32)))
        {
            cout << "ERROR : Failed to load texture " << rTextureName <<endl;
            return -1;
        }

        return 0;

    }

    sf::Texture render::Surface::GetTexture(){
        return this->texture;
    }


}

