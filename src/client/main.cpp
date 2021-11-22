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

int main(int argc,char* argv[]){

    sf::Clock clock;
    sf::Clock clockState;
    sf::Clock clockInter;
    RenderLayer lRender;
    State GameStatus(IN_COMBAT);
    int lMovingProgress = 0;
    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }
        else if(strcmp(argv[1], "render") == 0){

            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(60);
            lRender.LoadBackground();
            lRender.LoadCharacter(1,100,100,1);
            lRender.LoadCharacter(2,100,200,1);
            lRender.LoadCharacter(5,100,300,1);
            lRender.LoadCharacter(7,100,400,1);
            lRender.LoadEnemy(1, 600,250,0);
            lRender.LoadEnemy(3,600,250,0);
            lRender.LoadEnemy(1,600,250,0);
            lRender.LoadEnemy(2,600,250,0);

            int lEnemyIndex=0;
            int compteur=0;

            lRender.LoadUI();


            while (window.isOpen()){
                 Event event;
            while (window.pollEvent(event)){
                if ((event.type == Event::Closed)){
                        window.close();
                    }
             if(lEnemyIndex==4){
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
                        if(lMovingProgress%800!=0||(lMovingProgress==0)){
                            lMovingProgress = lRender.GoNextCombat(window);
                        }

                        else if(lMovingProgress%800==0){
                            GameStatus.SetCombatState(IN_COMBAT);
                            clockInter.restart();
                            
                            
                        }
                         break;
                }
                if((lMovingProgress%800==0)){
                    compteur++;
                    
                    if(compteur==100){
                        GameStatus.SetCombatState(OUT_COMBAT);
                        lMovingProgress = lRender.GoNextCombat(window);
                        lEnemyIndex++;
                        compteur=0;
                        }
                }




                

            
            

                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    lRender.AnimateCharacters();
                    clock.restart();
                }

                
                if(clockState.getElapsedTime().asSeconds() > 15.f && clockState.getElapsedTime().asSeconds() < 16.f){
                    GameStatus.SetCombatState(OUT_COMBAT);
                    lEnemyIndex=1;
                    
                }
                

                

                lRender.draw(window, lEnemyIndex,GameStatus);
                    
                window.display();  

                    
            }  
        }     


        
            

    


    
    }
    return 0;
}
