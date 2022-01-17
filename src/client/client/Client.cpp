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
        Character lNewEnemyCharacter;
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
        int lEnemyIndex = 0;
        lRender.LoadUI();
        


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
                            lPlayerCharacterPosition = lGameState->GetPlayerRosterSize(); // La position d'un nouveau joueur est l'index ajouté dans son roster
                            lNewEnemyCharacter = *(lGameState->GetEnemyCharacter());
                            lActiveEnemyCharacterNumber = lNewEnemyCharacter.GetCharacterNameNumber();

                            lRender.LoadBackground(lArena_Number); // Load first background (Arena 1 on game init)
                            lRender.UpdateCharacterOnScreen(lActivePlayerCharacterNumber, lPlayerCharacterPosition); // Sprite character joueur


                            lRender.UpdateCharacterOnScreen(lActiveEnemyCharacterNumber, 5); // Sprite character enemy
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
                        lNewEnemyCharacter = *(lGameState->GetEnemyCharacter()); // Save Enemy character before it change
                        canRunEngine = true;

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
            lRender.draw(rWindow, lEnemyIndex, lGameStatus);
                
            rWindow.display();
            
        }
        EngineUpdating(); //Last engine update to execute GAME_OVER instruction (print record)
        runFunctionCalled = false;
        GameEngine_Thread.join(); // Stop game thread



    }






}