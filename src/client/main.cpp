#include <engine.h>
#include <engine/WindowCursor.h>
#include <iostream>
#include <render/RenderLayer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <render/RenderLayer.h>
#include <engine.h>
#include <ai.h>
#include <engine/WindowCursor.h>
#include <client.h>


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
using namespace engine;
using namespace ai;
using namespace client;

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
            engine::WindowCursor lCursor;
            State GameStatus(IN_COMBAT, PLAYER_TURN);
            State Game_State(INITIALISATION, PLAYER_TURN);

            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(120);
            lRender.LoadBackground(1);
            lRender.LoadCharacter(1,1,250,250,1);
            lRender.LoadCharacter(2,2,200,300,1);
            lRender.LoadCharacter(3,5,150,350,1);
            lRender.LoadCharacter(4,7,100,400,1);
            lRender.LoadEnemy(1, 600,325,0);
            lRender.LoadEnemy(3,600,325,0);
            lRender.LoadEnemy(1,600,325,0);
            lRender.LoadEnemy(2,600,325,0);
            

            int lEnemyIndex=0;
        

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
            int player_turn = 1;

            sf::Clock clock;
            sf::Clock clockState;
            sf::Clock clockInter;
            sf::Clock GameClock;
            RenderLayer lRender;
            sf:: Vector2i LocalPosition;
            engine::WindowCursor lCursor;
            State Debug_State(IN_COMBAT, PLAYER_TURN);
            
            CombatStatus GameStatus = IN_COMBAT;
            State* Game_State;
            lRender.AddEngineObserver(&GameEngine);
            NewPlayer.AddEngineObserver(&GameEngine);
            NewIA.AddEngineObserver(&GameEngine);

            CommandID PlayerCommand[] = {engine::ATTACK_1, engine::ATTACK_1, engine::ATTACK_1};
            CommandID IACommand[] = {engine::ATTACK_2, engine::SPELL_1, engine::ATTACK_1};

            RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
            window.setFramerateLimit(120);
            lRender.LoadBackground(1);
            lRender.LoadCharacter(1, 1,250,250,1);
            lRender.LoadCharacter(2,9,200,300,1);
            lRender.LoadCharacter(3,12,150,350,1);
            lRender.LoadCharacter(4,13,100,400,1);
            lRender.LoadEnemy(9, 600,325,0);
            lRender.LoadEnemy(9,600,325,0);
            lRender.LoadEnemy(9,600,325,0);
            lRender.LoadEnemy(9,600,325,0);
            lRender.LoadUI();
            lRender.NotifyEndRendering();
            
            int lEnemyIndex=0;


            //lRender.LoadUI();


            while (window.isOpen()){
                 Event event;
            while (window.pollEvent(event)){
                if ((event.type == Event::Closed)){
                        window.close();
                    }
                    

                }
                window.clear();
                if(lCursor.ClickAction4(window)){
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
                           /* Debug_State.SetCombatState(OUT_COMBAT);
                            lEnemyIndex=1;
                            //LocalPosition = sf::Mouse::getPosition(window);
                            LocalPosition = sf::Mouse::getPosition(window);
                            std::cout << LocalPosition.x << ";" << LocalPosition.y << endl;  */
                    
                    
                    }
                }
                
                lCursor.GetPositionCursor(window);

                if(GameClock.getElapsedTime().asSeconds() > 3.f){
                    if(turn%2 == 0 ||player_turn==1){
                        NewPlayer.ClickCommand(window,lCursor);
                        player_turn=0;
                    }

                    else if(turn%2==1 || player_turn==0){
                        NewIA.SetStatusCommand(PlayerCommand[turn]);
                        player_turn=1;
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
        RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
        window.setFramerateLimit(60);

        Engine GameEngine;
        Clock lGameClock;
        Clock lRenderClock;
        RenderLayer lRender(&GameEngine);
        WindowCursor lPlayerCursor;
        Player lNewPlayer;
        State* lGameState = GameEngine.GetGameState();
        CombatStatus lGameStatus = GameEngine.GetGameStatus();
        Character* lNewPlayerCharacter;
        Character lNewEnemyCharacter;
        RandomAI IA_1;
        RandomAI IA_2;

        IA_1.AddEngineObserver(&GameEngine);
        IA_2.AddEngineObserver(&GameEngine);
        lNewPlayer.AddEngineObserver(&GameEngine);

        int lActivePlayerCharacterNumber = 0;
        int lActiveEnemyCharacterNumber = 0;
        int lPlayerCharacterPosition = 0;
        int lMovingProgress = 0;
        int lTurn = 0;
        int lLastCharacterDied_Index = 0;
        bool lIsCharacterAdd;
        bool lIsInitiated = false;
        static int lArena_Number = 1;
        int lEnemyIndex = 0;
        lRender.LoadUI();
        

        while(lGameStatus != GAME_OVER){  
          //  lGameState = GameEngine.GetGameState(); // Update actual state of the game
            lGameStatus = GameEngine.GetGameStatus(); // Update game status
            lTurn = lGameState->GetTurn(); //Update current turn       
            Event event;
            while (window.pollEvent(event)){

                if ((event.type == Event::Closed)){
                    cout << "Closing window" << endl;
                    window.close();
                    lGameStatus = GAME_OVER;
                }
            
            }
            window.clear();
            
                switch(lGameStatus){
                    
                    case INITIALISATION:
                        /**
                         * @brief Loading of player and enemy sprite on first turn
                         * 
                         */
                        if(!lIsInitiated){                            
                            lNewPlayerCharacter = lGameState->GetActivePlayerCharacter();
                            lActivePlayerCharacterNumber = lNewPlayerCharacter->GetCharacterNameNumber();
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize(); // La position d'un nouveau joueur est l'index ajouté dans son roster
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lActiveEnemyCharacterNumber = lNewEnemyCharacter.GetCharacterNameNumber();

                            lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                            lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition); // Sprite character joueur


                            lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 5); // Sprite character enemy
                            lRender.NotifyEndRendering();
                            
                            lIsInitiated = true;
                        }
                        
                        break;

                    case IN_COMBAT:
                    /**
                     * @brief Generate AI command, or wait for player command 
                     * 
                     */
                        lIsCharacterAdd = false;
                        lRender.DEBUG_SetRenderState(IN_COMBAT);

                        if(lGameClock.getElapsedTime().asSeconds() > 5){
                            if(lTurn%2 == 0){
                                IA_1.GenerarateRandomCommand();

                            }

                            else{
                                IA_2.GenerarateRandomCommand();
                               

                            }
                            lGameClock.restart();


                        } 
                        lRender.RefreshLifePoints(lGameState->mPlayersCharacters);
                        break;
                        
                    case OUT_COMBAT:
                    /**
                     * @brief Compute game instruction when combat finished (add enemy character in player team)
                     * 
                     */
                        lNewEnemyCharacter = *(lGameState->GetEnemyCharacter()); // Save Enemy character before it change
                        

                        break;

                    case RENDER_PROCESSING:
                    /**
                     * @brief Add new player team character on screen, change view to next combat zone/arena
                     * 
                     */
                        lRender.DEBUG_SetRenderState(RENDER_PROCESSING);
                        lPlayerCharacterPosition = lGameState->GetPlayerRosterSize();

                      //  cout << "Player roster size = " << lPlayerCharacterPosition << endl;

                        if((!lIsCharacterAdd) && lGameState->GetPlayerRosterSize() < lGameState->MAX_CHARACTER+1){/**
                            * @brief Ne fonctionne plus au delà du combat 2, cf. #64
                            * 
                            */
                            
                             // Récupération de la taille de l'équipe du joueur
                            lNewPlayerCharacter = lGameState->GetPlayerCharacter(lPlayerCharacterPosition);
                            lRender.UpdateCharacterOnScreen((int)lNewEnemyCharacter.GetCharacterNameNumber(), lPlayerCharacterPosition);
                            
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lRender.UpdateCharacterOnScreen((int)lNewEnemyCharacter.GetCharacterNameNumber(), 5);        
                            lEnemyIndex++;                    
                            lIsCharacterAdd = true;
                        }   

                        if(lArena_Number != lGameState->GetArenaNumber()){ // If arena change
                            lArena_Number = lGameState->GetArenaNumber(); // Get new arena number
                            lRender.LoadBackground(lArena_Number); // Load it 
                            lRender.GoNextArena();
                            lRender.NotifyEndRendering();
                        }
  
                        else{
                            lMovingProgress = lRender.GoNextCombat(window);
                            
                        }

                        break;

                    

            }

            
            /**
             * @brief Next lines verify if one of the character of the played died, in order to not render it anymore
             * 
             */
            lLastCharacterDied_Index = lGameState->GetLastPlayerCharacterDied();

            if(lLastCharacterDied_Index != -1){
                lRender.UnloadPlayerSpriteCharacter(lLastCharacterDied_Index);
            }


            


            if(lRenderClock.getElapsedTime().asSeconds() > 0.1f){
                lRender.AnimateCharacters();
                lRenderClock.restart();
            }
            
            lGameState = GameEngine.GameLoop();
            lTurn = lGameState->GetTurn();
            lPlayerCursor.GetPositionCursor(window);
            lRender.draw(window, lEnemyIndex, lGameStatus);
                
            window.display();
            
        }





        }
    

    else if(strcmp(argv[1], "heuristic_ai") == 0){
        RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
        window.setFramerateLimit(60);

        Engine GameEngine;
        Clock lGameClock;
        Clock lRenderClock;
        RenderLayer lRender(&GameEngine);
        WindowCursor lPlayerCursor;
        Player lNewPlayer;
        State* lGameState = GameEngine.GetGameState();
        CombatStatus lGameStatus = GameEngine.GetGameStatus();
        Character* lNewPlayerCharacter;
        Character lNewEnemyCharacter;
        HeuristicAI IA_1;
        HeuristicAI IA_2;

        IA_1.AddEngineObserver(&GameEngine);
        IA_2.AddEngineObserver(&GameEngine);
        lNewPlayer.AddEngineObserver(&GameEngine);

        int lActivePlayerCharacterNumber = 0;
        int lActiveEnemyCharacterNumber = 0;
        int lPlayerCharacterPosition = 0;
        int lMovingProgress = 0;
        int lTurn = 0;
        int lLastCharacterDied_Index = 0;
        bool lIsCharacterAdd;
        bool lIsInitiated = false;
        static int lArena_Number = 1;
        int lEnemyIndex = 0;
        lRender.LoadUI();
        

        while(lGameStatus != GAME_OVER){  
          //  lGameState = GameEngine.GetGameState(); // Update actual state of the game
            lGameStatus = GameEngine.GetGameStatus(); // Update game status
            lTurn = lGameState->GetTurn(); //Update current turn       
            Event event;
            while (window.pollEvent(event)){

                if ((event.type == Event::Closed)){
                    cout << "Closing window" << endl;
                    window.close();
                    lGameStatus = GAME_OVER;
                }
            
            }
            window.clear();
            
                switch(lGameStatus){
                    
                    case INITIALISATION:
                        /**
                         * @brief Loading of player and enemy sprite on first turn
                         * 
                         */
                        if(!lIsInitiated){                            
                            lNewPlayerCharacter = lGameState->GetActivePlayerCharacter();
                            lActivePlayerCharacterNumber = lNewPlayerCharacter->GetCharacterNameNumber();
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize(); // La position d'un nouveau joueur est l'index ajouté dans son roster
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lActiveEnemyCharacterNumber = lNewEnemyCharacter.GetCharacterNameNumber();

                            lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                            lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition); // Sprite character joueur


                            lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 5); // Sprite character enemy
                            lRender.NotifyEndRendering();
                            
                            lIsInitiated = true;
                        }
                        
                        break;

                    case IN_COMBAT:
                    /**
                     * @brief Generate AI command, or wait for player command 
                     * 
                     */
                        lIsCharacterAdd = false;
                        lRender.DEBUG_SetRenderState(IN_COMBAT);

                        if(lGameClock.getElapsedTime().asSeconds() > 3){
                            if(lTurn%2 == 0){
                                IA_1.GenerateHeuristicCommand();

                            }

                            else{
                                IA_2.GenerateHeuristicCommand();
                               

                            }
                            lGameClock.restart();


                        } 
                        lRender.RefreshLifePoints(lGameState->mPlayersCharacters);
                        break;
                        
                    case OUT_COMBAT:
                    /**
                     * @brief Compute game instruction when combat finished (add enemy character in player team)
                     * 
                     */
                        lNewEnemyCharacter = *(lGameState->GetEnemyCharacter()); // Save Enemy character before it change
                        

                        break;

                    case RENDER_PROCESSING:
                    /**
                     * @brief Add new player team character on screen, change view to next combat zone/arena
                     * 
                     */
                        lRender.DEBUG_SetRenderState(RENDER_PROCESSING);
                        lPlayerCharacterPosition = lGameState->GetPlayerRosterSize();

                      //  cout << "Player roster size = " << lPlayerCharacterPosition << endl;

                        if((!lIsCharacterAdd) && lGameState->GetPlayerRosterSize() < lGameState->MAX_CHARACTER+1){/**
                            * @brief Ne fonctionne plus au delà du combat 2, cf. #64
                            * 
                            */
                            
                             // Récupération de la taille de l'équipe du joueur
                            lNewPlayerCharacter = lGameState->GetPlayerCharacter(lPlayerCharacterPosition);
                            lRender.UpdateCharacterOnScreen((int)lNewEnemyCharacter.GetCharacterNameNumber(), lPlayerCharacterPosition);
                            
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lRender.UpdateCharacterOnScreen((int)lNewEnemyCharacter.GetCharacterNameNumber(), 5);        
                            lEnemyIndex++;                    
                            lIsCharacterAdd = true;
                        }   

                        if(lArena_Number != lGameState->GetArenaNumber()){ // If arena change
                            lArena_Number = lGameState->GetArenaNumber(); // Get new arena number
                            lRender.LoadBackground(lArena_Number); // Load it 
                            lRender.GoNextArena();
                            lRender.NotifyEndRendering();
                        }
  
                        else{
                            lMovingProgress = lRender.GoNextCombat(window);
                            
                        }

                        break;

                    

            }

            
            /**
             * @brief Next lines verify if one of the character of the played died, in order to not render it anymore
             * 
             */
            lLastCharacterDied_Index = lGameState->GetLastPlayerCharacterDied();

            if(lLastCharacterDied_Index != -1){
                lRender.UnloadPlayerSpriteCharacter(lLastCharacterDied_Index);
            }


            


            if(lRenderClock.getElapsedTime().asSeconds() > 0.1f){
                lRender.AnimateCharacters();
                lRenderClock.restart();
            }
            
            lGameState = GameEngine.GameLoop();
            lTurn = lGameState->GetTurn();
            lPlayerCursor.GetPositionCursor(window);
            lRender.draw(window, lEnemyIndex, lGameStatus);
                
            window.display();
            
        }





    }




    

    

    else if(strcmp(argv[1], "deep_ai") == 0){
        RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
        window.setFramerateLimit(60);

        Engine GameEngine;
        Clock lGameClock;
        Clock lRenderClock;
        RenderLayer lRender(&GameEngine);
        WindowCursor lPlayerCursor;
        Player lNewPlayer;
        State* lGameState = GameEngine.GetGameState();
        CombatStatus lGameStatus = GameEngine.GetGameStatus();
        Character* lNewPlayerCharacter;
        Character lNewEnemyCharacter;
        DeepAI IA_1(5);
        DeepAI IA_2(5);

        IA_1.AddEngineObserver(&GameEngine);
        IA_2.AddEngineObserver(&GameEngine);
        lNewPlayer.AddEngineObserver(&GameEngine);

        int lActivePlayerCharacterNumber = 0;
        int lActiveEnemyCharacterNumber = 0;
        int lPlayerCharacterPosition = 0;
        int lMovingProgress = 0;
        int lTurn = 0;
        int lLastCharacterDied_Index = 0;
        bool lIsCharacterAdd;
        bool lIsInitiated = false;
        static int lArena_Number = 1;
        int lEnemyIndex = 0;
        lRender.LoadUI();
        

        while(lGameStatus != GAME_OVER){  
          //  lGameState = GameEngine.GetGameState(); // Update actual state of the game
            lGameStatus = GameEngine.GetGameStatus(); // Update game status
            lTurn = lGameState->GetTurn(); //Update current turn       
            Event event;
            while (window.pollEvent(event)){

                if ((event.type == Event::Closed)){
                    cout << "Closing window" << endl;
                    window.close();
                    lGameStatus = GAME_OVER;
                }
            
            }
            window.clear();
            
                switch(lGameStatus){
                    
                    case INITIALISATION:
                        /**
                         * @brief Loading of player and enemy sprite on first turn
                         * 
                         */
                        if(!lIsInitiated){                            
                            lNewPlayerCharacter = lGameState->GetActivePlayerCharacter();
                            lActivePlayerCharacterNumber = lNewPlayerCharacter->GetCharacterNameNumber();
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize(); // La position d'un nouveau joueur est l'index ajouté dans son roster
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lActiveEnemyCharacterNumber = lNewEnemyCharacter.GetCharacterNameNumber();

                            lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                            lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition); // Sprite character joueur


                            lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 5); // Sprite character enemy
                            lRender.NotifyEndRendering();
                            
                            lIsInitiated = true;
                        }
                        
                        break;

                    case IN_COMBAT:
                    /**
                     * @brief Generate AI command, or wait for player command 
                     * 
                     */
                        lIsCharacterAdd = false;
                        lRender.DEBUG_SetRenderState(IN_COMBAT);

                        if(lGameClock.getElapsedTime().asSeconds() > 1){
                            if(lTurn%2 == 0){
                                IA_1.GenerateDeepCommand(5); // Generate optimal command
                                IA_1.ResetTree(); // Reset game tree for next turn
                                // lNewPlayer.ClickCommand(window,lPlayerCursor);
                               
                            
                    
                            }

                            else{
                                IA_2.GenerateDeepCommand(5);
                                IA_2.ResetTree();
                               

                            }
                            lGameClock.restart();


                        } 
                        lRender.RefreshLifePoints(lGameState->mPlayersCharacters);
                        break;
                        
                    case OUT_COMBAT:
                    /**
                     * @brief Compute game instruction when combat finished (add enemy character in player team)
                     * 
                     */
                        lNewEnemyCharacter = *(lGameState->GetEnemyCharacter()); // Save Enemy character before it change
                        

                        break;

                    case RENDER_PROCESSING:
                    /**
                     * @brief Add new player team character on screen, change view to next combat zone/arena
                     * 
                     */
                        lRender.DEBUG_SetRenderState(RENDER_PROCESSING);
                        lPlayerCharacterPosition = lGameState->GetPlayerRosterSize();

                      //  cout << "Player roster size = " << lPlayerCharacterPosition << endl;

                        if((!lIsCharacterAdd) && lGameState->GetPlayerRosterSize() < lGameState->MAX_CHARACTER+1){/**
                            * @brief Ne fonctionne plus au delà du combat 2, cf. #64
                            * 
                            */
                            
                             // Récupération de la taille de l'équipe du joueur
                            lNewPlayerCharacter = lGameState->GetPlayerCharacter(lPlayerCharacterPosition);
                            lRender.UpdateCharacterOnScreen((int)lNewEnemyCharacter.GetCharacterNameNumber(), lPlayerCharacterPosition);
                            
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lRender.UpdateCharacterOnScreen((int)lNewEnemyCharacter.GetCharacterNameNumber(), 5);        
                            lEnemyIndex++;                    
                            lIsCharacterAdd = true;
                        }   

                        if(lArena_Number != lGameState->GetArenaNumber()){ // If arena change
                            lArena_Number = lGameState->GetArenaNumber(); // Get new arena number
                            lRender.LoadBackground(lArena_Number); // Load it 
                            lRender.GoNextArena();
                            lRender.NotifyEndRendering();
                        }
  
                        else{
                            lMovingProgress = lRender.GoNextCombat(window);
                            
                        }

                        break;

                    

            }

            
            /**
             * @brief Next lines verify if one of the character of the played died, in order to not render it anymore
             * 
             */
            lLastCharacterDied_Index = lGameState->GetLastPlayerCharacterDied();

            if(lLastCharacterDied_Index != -1){
                lRender.UnloadPlayerSpriteCharacter(lLastCharacterDied_Index);
            }


            


            if(lRenderClock.getElapsedTime().asSeconds() > 0.1f){
                lRender.AnimateCharacters();
                lRenderClock.restart();
            }
            
            lGameState = GameEngine.GameLoop();
            lTurn = lGameState->GetTurn();
            lPlayerCursor.GetPositionCursor(window);
            lRender.draw(window, lEnemyIndex, lGameStatus);
                
            window.display();
            
        }





    }

    



    

    else if(strcmp(argv[1], "thread") == 0){

        Client client;
        
        RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
        window.setFramerateLimit(60);

        
        while (window.isOpen()){
            client.Run(window);
            sleep(2);
            window.close();

        }
    }

    else if(strcmp(argv[1], "network") == 0){
        if(argv[2] == NULL || argv[3] == NULL){
            cout << "Please specify host and port" << endl;
            cout << "./bin/server network <host> <port>" << endl;
            return -1;
        }
        char* lHost = argv[2];
        char* lPort = argv[3];

        NetworkClient Net_client(lHost, lPort);
        
        RenderWindow window(VideoMode(800, 600, 32), "ENSEAi");
        window.setFramerateLimit(60);

        
        while (window.isOpen()){
            if(Net_client.ConnectTo() == -1){
                return -1;
            }

            Net_client.RunNetwork(window);
            sleep(2);
            window.close();



        }
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
    




    
