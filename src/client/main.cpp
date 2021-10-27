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

    Surface test;
    sf::Sprite sprite;

    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }
            

    }

    RenderWindow app(VideoMode(800, 600, 32), "ENSEAi");

    // test.LoadTexture("ENSEA_logo.png");
    // sprite.setTexture(test.GetTexture());
    test.LoadTexture("ENSEA_logo.png");
    while (app.isOpen())
    {

        Event event;

        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed){
                app.close();
            }
            

        }
            app.clear(Color::Black);

            test.TestTransform();


            test.Draw(app);
            app.display();  
    }

    return 0;
}
