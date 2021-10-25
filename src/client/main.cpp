#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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


int main(int argc,char* argv[])
{
    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }
            

    }

    RenderWindow app(VideoMode(800, 600, 32), "Ma premiere fenetre SFML ! ");



    return 0;
}
