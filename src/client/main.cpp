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
    sf::Clock clockState;

    RenderLayer lRender;
    State GameStatus(IN_COMBAT);
    int lMovingProgress = 0;


    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }


        else if(strcmp(argv[1], "render") == 0){
            
            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(120);
            lRender.LoadBackground();
            sf::Vector2i LocalPosition;

            lRender.LoadCharacter(9,100,100);
            lRender.LoadCharacter(5,100,200);
            lRender.LoadCharacter(8,100,300);
            lRender.LoadCharacter(7,100,400);
            
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
                
                /*TEST DE LA MODIFICATION DU RENDU EN FONCTION DE L'ETAT DU JEU*/
                switch(GameStatus.GetCombatState()){
                    case IN_COMBAT:
                        lRender.DEBUG_SetRenderState(IN_COMBAT);
                        break;

                    case OUT_COMBAT:
                        lRender.DEBUG_SetRenderState(OUT_COMBAT);
                        if(lMovingProgress < 800){
                            lMovingProgress = lRender.GoNextCombat(window);
                        }

                        else if(lMovingProgress == 800){
                            GameStatus.SetCombatState(IN_COMBAT);
                        }
                        break;




                }


                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    lRender.AnimateCharacters();
                    clock.restart();
                }

                
                /* if(clockState.getElapsedTime().asSeconds() > 5.f && clockState.getElapsedTime().asSeconds() < 6.f){
                    GameStatus.SetCombatState(OUT_COMBAT);
                    
                } */

                if(lMovingProgress==0){
                    if((sf::Mouse::getPosition(window).y>510) && (sf::Mouse::getPosition(window).y<535) && 
                    (sf::Mouse::getPosition(window).x>35) && (sf::Mouse::getPosition(window).x<120)){
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            //GameStatus.SetCombatState(OUT_COMBAT);

                            //LocalPosition = sf::Mouse::getPosition(window);
                            LocalPosition = sf::Mouse::getPosition(window);
                            //std::cout << LocalPosition.x << ";" << LocalPosition.y << endl;
                            std::cout << "Action 1" << endl;
                    
                    }
                    }

                    if((sf::Mouse::getPosition(window).y>550) && (sf::Mouse::getPosition(window).y<575) && 
                    (sf::Mouse::getPosition(window).x>35) && (sf::Mouse::getPosition(window).x<120)){
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            //GameStatus.SetCombatState(OUT_COMBAT);

                            //LocalPosition = sf::Mouse::getPosition(window);
                            LocalPosition = sf::Mouse::getPosition(window);
                            //std::cout << LocalPosition.x << ";" << LocalPosition.y << endl;
                            std::cout << "Action 2" << endl;
                    
                    }
                    }
                }
                

                

                

                lRender.draw(window);
                    
                window.display();  

                    
            }       


        }
            

    }


    

    return 0;
}
