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

    RenderLayer lRender;

    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }


        else if(strcmp(argv[1], "render") == 0){
            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            lRender.LoadBackground();

            while (window.isOpen())
            {

                Event event;

                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed){
                        window.close();
                    }
                    

                }
                window.clear(Color::Black);

                    /*ZONE DE DESSIN*/
                    
                    lRender.draw(window);
                    


                    /*FIN ZONE DE DESSIN*/
                
                
                    //lDrawSurface.Draw(window);
                window.display();  

                    
            }       


        }
            

    }

    

    return 0;
}
