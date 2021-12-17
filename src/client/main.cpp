#include <client.h>
#include <client/WindowCursor.h>
#include <iostream>
#include <render/RenderLayer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <render/RenderLayer.h>
#include <client.h>
#include <ai.h>
#include <client/WindowCursor.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML
// fonctionne
#include <SFML/Graphics.hpp>

void testSFML() { sf::Texture texture; }

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace client;
using namespace ai;

int main(int argc,char* argv[]){



    int lMovingProgress = 1;
    if(argc > 1){
        if(strcmp(argv[1], "hello") == 0){
            cout << "Bonjour le monde" << endl;
        }
        else if(strcmp(argv[1], "render") == 0){
            sf::Clock clock;
            sf::Clock clockState;
            sf::Clock clockInter;
            sf::Clock Input_Clock;
            RenderLayer lRender;
            sf:: Vector2i LocalPosition;
            client::WindowCursor lCursor;
            State GameStatus(IN_COMBAT, PLAYER_TURN);
            State Game_State(INITIALISATION, PLAYER_TURN);

            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(120);
            lRender.LoadBackground();
            lRender.LoadCharacter(1,250,250,1);
            lRender.LoadCharacter(2,200,300,1);
            lRender.LoadCharacter(5,150,350,1);
            lRender.LoadCharacter(7,100,400,1);
            lRender.LoadEnemy(1, 600,325,0);
            lRender.LoadEnemy(3,600,325,0);
            lRender.LoadEnemy(1,600,325,0);
            lRender.LoadEnemy(2,600,325,0);
            

            int lEnemyIndex=0;
            int compteur=0;

            //lRender.LoadUI();


            while (window.isOpen()){
                 Event event;
            while (window.pollEvent(event)){
                if ((event.type == Event::Closed)){
                        window.close();
                    }
             if(lEnemyIndex==4){
                    window.close();
                }
            if(lCursor.ClickAction4(window)){
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
                    
                    if(lCursor.ClickAction1(window)){
                        GameStatus.SetCombatState(OUT_COMBAT);
                        lMovingProgress = lRender.GoNextCombat(window);
                        lEnemyIndex++;
                        
                    }
                }




                

            
            

                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    lRender.AnimateCharacters();
                    clock.restart();
                }

                if(lMovingProgress==1){
                    lRender.LoadUI();
                    lCursor.GetPositionCursor(window);
                    if(lCursor.ClickAction1(window)){
                            GameStatus.SetCombatState(OUT_COMBAT);
                            lEnemyIndex=1;
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
                

                

                lRender.draw(window, lEnemyIndex,GameStatus.GetCombatState());
                    
                window.display();  

                    
            }  
        }     

    
        else if(strcmp(argv[1], "engine") == 0){
            Engine GameEngine;
            Player NewPlayer;
            RandomAI NewIA;
            int turn = 0;

            sf::Clock clock;
            sf::Clock clockState;
            sf::Clock clockInter;
            sf::Clock GameClock;
            RenderLayer lRender;
            sf:: Vector2i LocalPosition;
            client::WindowCursor lCursor;
            State Debug_State(IN_COMBAT, PLAYER_TURN);
            
            CombatStatus GameStatus = IN_COMBAT;
            State* Game_State;

            NewPlayer.AddEngineObserver(&GameEngine);
            NewIA.AddEngineObserver(&GameEngine);

            CommandID PlayerCommand[] = {client::ATTACK_1, client::ATTACK_1, client::ATTACK_1};
            CommandID IACommand[] = {client::ATTACK_2, client::SPELL_1, client::ATTACK_1};

            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(120);
            lRender.LoadBackground();
            lRender.LoadCharacter(1,250,250,1);
            lRender.LoadCharacter(9,200,300,1);
            lRender.LoadCharacter(12,150,350,1);
            lRender.LoadCharacter(13,100,400,1);
            lRender.LoadEnemy(9, 600,325,0);
            lRender.LoadEnemy(9,600,325,0);
            lRender.LoadEnemy(9,600,325,0);
            lRender.LoadEnemy(9,600,325,0);
            lRender.LoadUI();


            int lEnemyIndex=0;
            int compteur=0;

            //lRender.LoadUI();


            while (window.isOpen()){
                 Event event;
            while (window.pollEvent(event)){
                if ((event.type == Event::Closed)){
                        window.close();
                    }
                    

                }
                window.clear();
                if(lEnemyIndex==4){
                        window.close();
                }


                /*TEST DE LA MODIFICATION DU RENDU EN FONCTION DE L'ETAT DU JEU*/
                switch(GameStatus){
                    case IN_COMBAT:
                        
                        lRender.DEBUG_SetRenderState(IN_COMBAT);
                        break;

                    case OUT_COMBAT:
                        lRender.DEBUG_SetRenderState(OUT_COMBAT);
                        if(lMovingProgress%800!=0||(lMovingProgress==0)){
                            lMovingProgress = lRender.GoNextCombat(window);
                        }

                        else if(lMovingProgress%800==0){
                            
                            Debug_State.SetCombatState(IN_COMBAT);
                            clockInter.restart();
                            
                            
                        }
                         break;
                }
                if((lMovingProgress%800==0)){
                    
                    /* if(lCursor.ClickAction1(window)){
                        GameStatus.SetCombatState(OUT_COMBAT);
                        lMovingProgress = lRender.GoNextCombat(window);
                        lEnemyIndex++;
                        
                    } */
                }
            
            

                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    lRender.AnimateCharacters();
                    clock.restart();
                }

                if(lMovingProgress==1){
                    lRender.LoadUI();
                    lCursor.GetPositionCursor(window);
                    if(lCursor.ClickAction1(window)){
                            Debug_State.SetCombatState(OUT_COMBAT);
                            lEnemyIndex=1;
                            //LocalPosition = sf::Mouse::getPosition(window);
                            LocalPosition = sf::Mouse::getPosition(window);
                            std::cout << LocalPosition.x << ";" << LocalPosition.y << endl;
                    
                    
                    }
                }
                
                lCursor.GetPositionCursor(window);

                if(GameClock.getElapsedTime().asSeconds() > 3.f){
                    if(turn%2 == 0){
                        NewPlayer.SetStatusCommand(PlayerCommand[turn]);
                    }

                    else{
                        NewIA.SetStatusCommand(PlayerCommand[turn]);
                    }
                    turn++;
                    Game_State = GameEngine.GameLoop(); // Update de l'état du jeu toutes les 3s pour + de visibilité
                    GameStatus = Game_State->GetCombatState();
                    GameClock.restart();
                }
                
                lRender.draw(window, lEnemyIndex,GameStatus);
                    
                window.display();  

                    
            }
        }
    

        else if(strcmp(argv[1], "random_ai") == 0){
            Engine GameEngine;
            Player NewPlayer;
            RandomAI IA_1;
            RandomAI IA_2;
           
            sf::Clock clock;
            sf::Clock clockState;
            sf::Clock clockInter;
            sf::Clock GameClock;
            RenderLayer lRender(&GameEngine);
            sf:: Vector2i LocalPosition;
            client::WindowCursor lCursor;
            State Debug_State(IN_COMBAT, PLAYER_TURN);
            State* Game_State;
            CombatStatus GameStatus = INITIALISATION;
            int turn = 0;
            Character* lActivePlayerCharacter;
            Character* lActiveEnemyCharacter;
            int lActivePlayerCharacterNumber = 0;
            int lActiveEnemyCharacterNumber = 0;
            int lPlayerCharacterPosition = 0;
            

            IA_1.AddEngineObserver(&GameEngine);
            IA_2.AddEngineObserver(&GameEngine);
            
            

            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(60);
            lRender.LoadBackground();
/*             lRender.LoadCharacter(1,250,250,1);
            lRender.LoadCharacter(2,200,300,1);
            lRender.LoadCharacter(5,150,350,1);
            lRender.LoadCharacter(7,100,400,1);
            lRender.LoadEnemy(1, 600,325,0);
            lRender.LoadEnemy(3,600,325,0);
            lRender.LoadEnemy(1,600,325,0);
            lRender.LoadEnemy(2,600,325,0); */
            lRender.LoadUI();


            int lEnemyIndex=0;
            int compteur=0;

            //lRender.LoadUI();


            while (window.isOpen()){
                 Event event;
            while (window.pollEvent(event)){
                if ((event.type == Event::Closed)){
                        window.close();
                    }
                    

                }
                window.clear();
                if(lEnemyIndex==4){
                    window.close();
                }

                if(GameClock.getElapsedTime().asSeconds() > 0.1f){
                    if(turn%2 == 0 && GameStatus == IN_COMBAT){
                        IA_1.GenerarateRandomCommand();
                    }

                    else if(GameStatus == IN_COMBAT){
                        IA_2.GenerarateRandomCommand();
                    }
                    
                    turn++;
                    Game_State = GameEngine.GameLoop(); // Update de l'état du jeu toutes les 3s pour + de visibilité
                    GameStatus = Game_State->GetCombatState();


                 //   lActiveCharacter = Game_State->GetPlayerRosterSize();
                    GameClock.restart();
                }

                /*MODIFICATION DU RENDU EN FONCTION DE L'ETAT DU JEU*/

                switch(GameStatus){
                    
                    case INITIALISATION:
                        /**
                         * @brief Chargement du sprite personnage player et ennemi tour 1
                         * 
                         */
                        
                        lActivePlayerCharacter = Game_State->GetActivePlayerCharacter();
                        lActivePlayerCharacterNumber = lActivePlayerCharacter->GetCharacterNameNumber();
                        lPlayerCharacterPosition = Game_State->GetPlayerRosterSize(); // La position d'un nouveau joueur est l'index ajouté dans son roster
                        lActiveEnemyCharacter = Game_State->GetEnemyCharacter();
                        lActiveEnemyCharacterNumber = lActiveEnemyCharacter->GetCharacterNameNumber();
                    
                        lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition); // Sprite character joueur
                        lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 4); // Sprite character enemy
                        lRender.NotifyEndRendering();
                        GameStatus = state::IN_COMBAT; /**
                        * @brief Changement tout de suite de l'état local du jeu pour ne plus faire d'intialisation
                        dans le cas où l'état local du jeu n'est pas tout de suite maj à cause du timer Gameclock
                        * 
                        */

                        
                        break;

                    case IN_COMBAT:
                        
                        lRender.DEBUG_SetRenderState(IN_COMBAT);
                        break;

                    case RENDER_PROCESSING:
                        lRender.DEBUG_SetRenderState(RENDER_PROCESSING);
                        
                            lMovingProgress = lRender.GoNextCombat(window);
    
                        break;
                }
                   
                if((lMovingProgress%800==0)){
                    
                    /* if(lCursor.ClickAction1(window)){
                        GameStatus.SetCombatState(OUT_COMBAT);
                        lMovingProgress = lRender.GoNextCombat(window);
                        lEnemyIndex++;
                        
                    } */
                }
            
            

                if(clock.getElapsedTime().asSeconds() > 0.1f){
                    lRender.AnimateCharacters();
                    clock.restart();
                }

                if(lMovingProgress==1){
                    lRender.LoadUI();
                    lCursor.GetPositionCursor(window);
                    if(lCursor.ClickAction1(window)){
                            Debug_State.SetCombatState(OUT_COMBAT);
                            lEnemyIndex=1;
                            //LocalPosition = sf::Mouse::getPosition(window);
                            LocalPosition = sf::Mouse::getPosition(window);
                            std::cout << LocalPosition.x << ";" << LocalPosition.y << endl;
                    
                    
                    }
                }
                
                lCursor.GetPositionCursor(window);


                
                lRender.draw(window, lEnemyIndex, GameStatus);
                    
                window.display();  

                    
            }
        }
    

    else if(strcmp(argv[1], "heuristic_ai") == 0){
        Engine NewEngine;
        
        HeuristicAI AI1;
        HeuristicAI AI2;
        State* Game_State;
        
        CombatStatus GameStatus = INITIALISATION;
        int turn = 0;

        
        AI1.AddEngineObserver(&NewEngine);
        AI2.AddEngineObserver(&NewEngine);

        while(GameStatus != GAME_OVER){

            if(turn%2 == 0 && GameStatus == IN_COMBAT){
                AI1.GenerateHeuristicCommand();
            }

            else if(GameStatus == IN_COMBAT){
                AI2.GenerateHeuristicCommand();
            }
            turn++;
            Game_State = NewEngine.GameLoop();
            GameStatus = Game_State->GetCombatState();
        }
        
        NewEngine.GameLoop();

        }

    



     else if(strcmp(argv[1], "test") == 0){
        Engine NewEngine;
        Player NewPlayer;
        HeuristicAI AI1;
        HeuristicAI AI2;
        
        State* Game_State;
        CombatStatus GameStatus = INITIALISATION;
        int turn = 0;

        NewPlayer.AddEngineObserver(&NewEngine);
        AI1.AddEngineObserver(&NewEngine);
        AI2.AddEngineObserver(&NewEngine);

        while(GameStatus != GAME_OVER){

            if(turn%2 == 0 && GameStatus == IN_COMBAT){
                //NewPlayer.
            }

            else if(GameStatus == IN_COMBAT){
                AI2.GenerateHeuristicCommand();
            }
            turn++;
            Game_State = NewEngine.GameLoop();
            GameStatus = Game_State->GetCombatState();
        }
        
        NewEngine.GameLoop();
        }
     }
    return 0;
}
    




    
