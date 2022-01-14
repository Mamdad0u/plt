#include <client/Client.h>  // Included from library shared_static
#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>

using namespace client;
using namespace render;
using namespace engine;
using namespace state;
using namespace sf;
using namespace std;
using namespace ai;

namespace client{

bool canRunEngine = false;
bool runFunctionCalled = true;

    void ThreadEngine(engine::Engine* rEngine){
        while(runFunctionCalled){
            // usleep(1000);
            if(canRunEngine){
                rEngine->GameLoop();
                canRunEngine = false;
            }

        }
        

    }


    void client::Client::EngineUpdating(){
        canRunEngine = true;
    }

    void client::Client::Run(sf::RenderWindow& rWindow){
        Clock lGameClock;
        Clock lRenderClock;
        RenderLayer lRender(&mGameEngine);
        WindowCursor lPlayerCursor;
        Player lNewPlayer;
        State* lGameState = mGameEngine.GetGameState();
        CombatStatus lGameStatus = mGameEngine.GetGameStatus();
        Character* lNewPlayerCharacter;
        Character* lNewEnemyCharacter;
        DeepAI IA_1(5);
        DeepAI IA_2(5);

        IA_1.AddEngineObserver(&mGameEngine);
        IA_2.AddEngineObserver(&mGameEngine);
        lNewPlayer.AddEngineObserver(&mGameEngine);

        int lActivePlayerCharacterNumber = 0;
        int lActiveEnemyCharacterNumber = 0;
        int lPlayerCharacterPosition = 0;
        int lMovingProgress = 0;
        int lTurn = 0;
        bool lIsCharacterAdd;
        bool lIsInitiated = false;
        static int lArena_Number = 1;
        lRender.LoadUI();



        thread t1(ThreadEngine, &mGameEngine);

        while(lGameStatus != GAME_OVER){  
          //  lGameState = mGameEngine.GetGameState(); // Update actual state of the game
            lGameStatus = mGameEngine.GetGameStatus(); // Update game status
            lTurn = lGameState->GetTurn(); //Update current turn       
            Event event;
            while (rWindow.pollEvent(event)){

                if ((event.type == Event::Closed)){
                    cout << "Closing window" << endl;
                    rWindow.close();
                    lGameStatus = GAME_OVER;
                }
            
            }
            rWindow.clear();
            
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
                            lNewEnemyCharacter = lGameState->GetEnemyCharacter();
                            lActiveEnemyCharacterNumber = lNewEnemyCharacter->GetCharacterNameNumber();

                            lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                            lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition-1); // Sprite character joueur
                            lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 4); // Sprite character enemy
                            lRender.NotifyEndRendering();
                            EngineUpdating();
                            lIsInitiated = true;
                            }
                        
                        break;

                    case IN_COMBAT:
                        lIsCharacterAdd = false;
                        lRender.DEBUG_SetRenderState(IN_COMBAT);

                        if(lGameClock.getElapsedTime().asSeconds() > 1.f){
                            if(lTurn%2 == 0){
                                IA_1.GenerateDeepCommand(5); // Generate optimal command
                                IA_1.ResetTree(); // Reset game tree for next turn
                                // lNewPlayer.ClickCommand(rWindow,lPlayerCursor);
                                EngineUpdating();
                            
                               
                            }

                            else{
                                IA_2.GenerateDeepCommand(5);
                                IA_2.ResetTree();
                                EngineUpdating();

                            }
                            lGameClock.restart();
                        } 
                        break;
                        
                    case OUT_COMBAT:
                    /*Ajout du sprite enemy dans la team du joueur*/
                        canRunEngine = true;

                        break;
                    case RENDER_PROCESSING:

                        lRender.DEBUG_SetRenderState(RENDER_PROCESSING);
                        
                        if(!lIsCharacterAdd){/**
                            * @brief Ne fonctionne plus au delà du combat 2, cf. #64
                            * 
                            */
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize() - 1; // Récupération de la taille de l'équipe du joueur
                            lNewPlayerCharacter = lGameState->GetPlayerCharacter(lPlayerCharacterPosition);
                            lNewEnemyCharacter = lGameState->GetEnemyCharacter();
                            lRender.UpdateCharacterOnScreen((int)lNewPlayerCharacter->GetCharacterNameNumber(), lPlayerCharacterPosition);
                            lRender.UpdateCharacterOnScreen(lNewEnemyCharacter->GetCharacterNameNumber(), 4);
                            lIsCharacterAdd = true;
                        }

                        if(lArena_Number != lGameState->GetArenaNumber()){ // If arena change
                            lArena_Number = lGameState->GetArenaNumber(); // Get new arena number
                            lRender.LoadBackground(lArena_Number); // Load it 
                            lRender.GoNextArena();
                            lRender.NotifyEndRendering();
                        }
  
                        else{
                            lMovingProgress = lRender.GoNextCombat(rWindow);
                            EngineUpdating();
                        }

                        break;
                
                            

            }

            

            if(lRenderClock.getElapsedTime().asSeconds() > 0.1f){
                lRender.AnimateCharacters();
                lRenderClock.restart();
            }
            lPlayerCursor.GetPositionCursor(rWindow);
            lRender.draw(rWindow, 0, lGameStatus);
                
            rWindow.display();
            
        }

        runFunctionCalled = false;
        t1.join();



    }






}