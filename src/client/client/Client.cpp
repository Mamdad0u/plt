#include <client/Client.h>  // Included from library shared_static
#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>

using namespace client;
using namespace render;
using namespace state;
using namespace sf;
using namespace std;

namespace client{

bool canRunEngine = true;
bool runFunctionCalled = true;

    void ThreadEngine(engine::Engine* rEngine){
        while(runFunctionCalled){
            usleep(1000);
            if(canRunEngine){
                rEngine->GameLoop();
               // canRunEngine = false;
            }

        }
        

    }


    void client::Client::EngineUpdating(){
        canRunEngine = true;
    }

    void client::Client::Run(sf::RenderWindow& rWindow){
        Clock clock;
        RenderLayer lRender(&mGameEngine);
        
        State* lGameState = mGameEngine.GetGameState();
        CombatStatus lGameStatus = mGameEngine.GetGameStatus();
        Character* lNewPlayerCharacter;
        Character* lNewEnemyCharacter;

        int lActivePlayerCharacterNumber = 0;
        int lActiveEnemyCharacterNumber = 0;
        int lPlayerCharacterPosition = 0;
        int lMovingProgress = 0;
        bool lIsCharacterAdd;

        static int lArena_Number = 1;
        lRender.LoadBackground(1);
        lRender.LoadUI();

        thread t1(ThreadEngine, &mGameEngine);

        while(lGameStatus != GAME_OVER){         
            Event event;
            while (rWindow.pollEvent(event)){

                if ((event.type == Event::Closed)){
                    cout << "Closing window" << endl;
                    rWindow.close();
                    lGameStatus == GAME_OVER;
                }
            
            }
            rWindow.clear();
            
                switch(lGameStatus){
                    
                    case INITIALISATION:
                        /**
                         * @brief Loading of player and enemy sprite on first turn
                         * 
                         */
                        
                        lNewPlayerCharacter = lGameState->GetActivePlayerCharacter();
                        lActivePlayerCharacterNumber = lNewPlayerCharacter->GetCharacterNameNumber();
                        lPlayerCharacterPosition = lGameState->GetPlayerRosterSize(); // La position d'un nouveau joueur est l'index ajouté dans son roster
                        lNewEnemyCharacter = lGameState->GetEnemyCharacter();
                        lActiveEnemyCharacterNumber = lNewEnemyCharacter->GetCharacterNameNumber();

                        lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                        lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition-1); // Sprite character joueur
                        lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 4); // Sprite character enemy
                        lRender.NotifyEndRendering();

                        
                        break;

                    case IN_COMBAT:
                        lIsCharacterAdd = false;
                        lRender.DEBUG_SetRenderState(IN_COMBAT);
                        break;
                        
                    case OUT_COMBAT:
                    /*Ajout du sprite enemy dans la team du joueur*/

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
                        }

                        break;
                
                            

            }
            if(clock.getElapsedTime().asSeconds() > 0.1f){
                lRender.AnimateCharacters();
                clock.restart();
            }

            lRender.draw(rWindow, 0, lGameStatus);
                
            rWindow.display();  
            runFunctionCalled = false;
            t1.join();
        }





    }






}