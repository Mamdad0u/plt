#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <render/Surface.h>

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

    Surface lDrawSurface;
    sf::Sprite sprite;

    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }


        else if(strcmp(argv[1], "render") == 0){
            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");

            lDrawSurface.LoadSurface("Rue_ENSEA_16Bits.jpg", 0, 0, 800, 600);          

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
                    
                   
                    


                    /*FIN ZONE DE DESSIN*/
                window.draw(lDrawSurface);
                
                    //lDrawSurface.Draw(window);
                window.display();  

                    
            }       


        }
            

    }

    

    return 0;
}
