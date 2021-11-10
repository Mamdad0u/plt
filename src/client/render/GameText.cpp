#include <render/GameText.h>  // Included from library shared_static
#include "GameText.h"
#include <iostream>

using namespace std;

namespace render {
    render::GameText::GameText(){
        if (!mFont.loadFromFile("res/font.ttf"))
        {
            cout << "ERROR : Failed to policy " << endl;
        }

        else{
            
        }
        


    }


}