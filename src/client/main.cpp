#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <render/RenderLayer.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>



using namespace std;
using namespace state;
using namespace sf;
using namespace render;

int main(int argc,char* argv[])
{
    sf::Clock clock;
    RenderLayer lRender;
    int lMovingProgress = 0;

    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }


        else if(strcmp(argv[1], "render") == 0){
            
            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            lRender.LoadBackground();
            //lRender.LoadCharacters(1, 200, 400);

            lRender.LoadCharacter(1,100,100);
            lRender.LoadCharacter(2,100,200);
            lRender.LoadCharacter(3,100,300);
            lRender.LoadCharacter(4,100,400);
            lRender.LoadUI();

            while (window.isOpen())
            {

                Event event;

                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed){
                        window.close();
                    }
                    

                }


                window.clear();

                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    lRender.AnimateCharacters();
                    clock.restart();
                }

                
/*                 if(lMovingProgress < 800){
                    lMovingProgress = lRender.GoNextCombat(window);
                } */
                

                

                lRender.draw(window);
                    
                window.display();  

                    
            }       


        }
            

    }


    

    return 0;
}
