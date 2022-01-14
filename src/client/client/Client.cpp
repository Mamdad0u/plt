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

/**
 * @brief Thread method of game engine. Run only when a command must be compute.
 * 
 * @param rEngine // Pointer to main game engine
 */
    void ThreadEngine(engine::Engine* rEngine){
        while(runFunctionCalled){ // Always true when game running
            // usleep(1000);
            if(canRunEngine){ // Only true when a command is to compute
                rEngine->GameLoop(); // Computation of command
                canRunEngine = false; // Back to standby
            }

        }
        

    }


    void client::Client::EngineUpdating(){
        canRunEngine = true;
    }

    /**
     * @brief Main thread method execution
     * 
     * @param rWindow Object reference to window created by sf in main()
     */

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
        int test = 0;


        thread GameEngine_Thread(ThreadEngine, &mGameEngine);

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
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize() - 1; // La position d'un nouveau joueur est l'index ajouté dans son roster
                            lNewEnemyCharacter = lGameState->GetEnemyCharacter();
                            lActiveEnemyCharacterNumber = lNewEnemyCharacter->GetCharacterNameNumber();

                            lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                            lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition); // Sprite character joueur


                            lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 4); // Sprite character enemy
                            lRender.NotifyEndRendering();
                            EngineUpdating();
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

                        if(lGameClock.getElapsedTime().asSeconds() > 0){
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
                    /**
                     * @brief Compute game instruction when combat finished (add enemy character in player team)
                     * 
                     */
                        canRunEngine = true;

                        break;

                    case RENDER_PROCESSING:
                    /**
                     * @brief Add new player team character on screen, change view to next combat zone/arena
                     * 
                     */
                        lRender.DEBUG_SetRenderState(RENDER_PROCESSING);
                        
                        if(!lIsCharacterAdd){/**
                            * @brief Ne fonctionne plus au delà du combat 2, cf. #64
                            * 
                            */
                            test++;
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize() - 1; // Récupération de la taille de l'équipe du joueur
                            lNewPlayerCharacter = lGameState->GetPlayerCharacter(lPlayerCharacterPosition);
                            lNewEnemyCharacter = lGameState->GetEnemyCharacter();
                            

                            switch (lPlayerCharacterPosition)
                            {
                            case 1:
                                lRender.UpdateCharacterOnScreen(2, 1);
                          //      lRender.UpdateCharacterOnScreen(5, 2);
                                break;
                            case 2:
                                
                                lRender.LoadCharacter(5,150,350,1);
                                break;
                            case 3:
                                lRender.UpdateCharacterOnScreen((int)lNewPlayerCharacter->GetCharacterNameNumber(), 3);
                                break;

                            }
                      //     lRender.UpdateCharacterOnScreen((int)lNewPlayerCharacter->GetCharacterNameNumber(), 2);
                            
                          //  lRender.UpdateCharacterOnScreen(lNewEnemyCharacter->GetCharacterNameNumber(), 4);
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
        EngineUpdating(); //Last engine update to execute GAME_OVER instruction (print record)
        runFunctionCalled = false;
        GameEngine_Thread.join(); // Stop game thread



    }






}