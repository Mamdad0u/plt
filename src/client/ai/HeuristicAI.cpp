#include <ai/HeuristicAI.h>  // Included from library shared_static
#include "HeuristicAI.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace engine;
using namespace state;

namespace ai {


    ai::HeuristicAI::HeuristicAI(){

    }



    engine::CommandID ai::HeuristicAI::GenerateHeuristicCommand(){
        const float lLife_threshold = 0.5f;
        CommandID lHeuristicCommand;
        std::list<EngineObserver*>::iterator lRunningEngine;
        lRunningEngine = this->mEngineObserverList.begin(); // Récupération des paramètres de l'engine 
        State lGameStatus = (*lRunningEngine)->mCurrentState; // Récupération de l'état du jeu depuis l'engine
        Character* lActiveCharacter; // Character actif joueur durant ce tour
        Character* lActiveEnemyCharacter;
        CharacterName lSpeciality;
        state::Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();

        const int lMax_luck = 25;
        const int lMax_Attack = 200;
        const int lMax_Defense = 200;

        int lAlivePlayer = lGameStatus.GetAlivePlayer();

        int lEnemy_MaxLifePoints = 0; 
        int lEnemy_LifePoints = 0;
        int lEnemy_Luck = 0;
        int lEnemy_Defense = 0;
        int lEnemy_Attack = 0;

        int lPlayer_MaxLifePoints = 0; 
        int lPlayer_LifePoints = 0;
        int lPlayer_Luck = 0;
        int lPlayer_Defense = 0;
        int lPlayer_Attack = 0;

        if(lPlayerTurn == IA_MIN_TURN){ // Si c'est le tour de l'IA joueur  de jouer
            lActiveCharacter = lGameStatus.GetActivePlayerCharacter(); // Récupération du character actif de l'IA joueur en train d'être joué
            lActiveEnemyCharacter = lGameStatus.GetEnemyCharacter();
        }

        else if((lPlayerTurn == IA_MAX_TURN)){ //  Si c'est le tour de l'IA enemy de jouer
            lActiveCharacter = lGameStatus.GetEnemyCharacter(); // Récupération de son character
            lActiveEnemyCharacter = lGameStatus.GetActivePlayerCharacter();
        }
        lSpeciality = lActiveCharacter->GetCharacterNameNumber();

        lEnemy_MaxLifePoints = lActiveEnemyCharacter->GetCharacterStats(MAX_LIFE_POINTS);
        lEnemy_LifePoints = lActiveEnemyCharacter->GetCharacterStats(LIFE_POINTS);
        lEnemy_Luck = lActiveEnemyCharacter->GetCharacterStats(LUCK);
        lEnemy_Defense = lActiveEnemyCharacter->GetCharacterStats(DEFENSE);
        lEnemy_Attack = lActiveEnemyCharacter->GetCharacterStats(ATTACK);

        lPlayer_MaxLifePoints = lActiveCharacter->GetCharacterStats(MAX_LIFE_POINTS);
        lPlayer_LifePoints = lActiveCharacter->GetCharacterStats(LIFE_POINTS);
        lPlayer_Luck = lActiveCharacter->GetCharacterStats(LUCK);
        lPlayer_Attack = lActiveCharacter->GetCharacterStats(ATTACK);

        /**
         * @brief Les lignes suivantes détaillent le fonctionnement du choix d'une commande selon des heuristiques
         * 
         */

        switch (lSpeciality)
        {
        case IS: // Polyvalent

            if(lPlayer_Attack < lMax_Attack){
                lHeuristicCommand = engine::SPELL_2;
            }

            else{ 
                lHeuristicCommand = engine::ATTACK_1; //On privilégie une attaque de dégats
            }
            break;
        
        case SIA: // Magicien
            
            if(lPlayer_Luck < lMax_luck){ // Priorité : augmenter sa luck
                lHeuristicCommand = engine::SPELL_2;
            }

            else if(lEnemy_Luck > 0){ // Sinon on cherche à baisser sa luck
                lHeuristicCommand = engine::SPELL_1;
            }

            else{ 
                lHeuristicCommand = engine::ATTACK_1; //On privilégie une attaque de dégats
            }

            break;

        case RT: // Attaquant
        
            if(lPlayer_Attack < lMax_Attack){ // Priorité : augmenter son attaque
                lHeuristicCommand = engine::SPELL_1; 
            }

            else if(lEnemy_Attack > 0){ // Sinon on cherche à baisser son attaque
                lHeuristicCommand = engine::SPELL_2;
            }

            else{ // Sinon attaque normale
                lHeuristicCommand = engine::ATTACK_1;
            }

            break;

        case MSC: // Tank

            if(lAlivePlayer >1 && lPlayerTurn == PLAYER_TURN){ // Si il y a encore plus d'un character dans la team player
                lHeuristicCommand = engine::SPELL_2; // buff de LP pour la team
            }


            
            else if(lPlayer_LifePoints < (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est < à 60%
                lHeuristicCommand = engine::SPELL_1; // On privilégie la montée de sa vie
           
            }

            else{ // Sinon 
                lHeuristicCommand = engine::ATTACK_1; //On privilégie une attaque de dégats
            }

            break;

        case AEI: // Attaquant
            if(lAlivePlayer >1 && lPlayerTurn == PLAYER_TURN){
                lHeuristicCommand = engine::SPELL_1; //Buff
            }

            else if(lPlayer_LifePoints > (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est > à 60%
                lHeuristicCommand = engine::ATTACK_2; //On privilégie une grosse attaque de dégats qui lui fait perdre de la vie 
            }

            else{
               lHeuristicCommand = engine::ATTACK_1; //On privilégie une attaque de dégats
            }
            break;

        case EVE: // Support/soin

            if(lAlivePlayer >1 && lPlayerTurn == PLAYER_TURN){ // Si il y a encore plus d'un character dans la team player
                lHeuristicCommand = engine::SPELL_2;
            }

            else if(lPlayer_LifePoints < (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est < à 60%
                lHeuristicCommand = engine::SPELL_1; // On privilégie la montée de sa vie
           
            }

            else{ // Sinon on privilégie une attaque de dégats
                lHeuristicCommand = engine::ATTACK_1; 
            }
            break;

        case ESE: // Tank
            if(lPlayer_Defense < lMax_Defense){
                lHeuristicCommand = engine::SPELL_1; // Il monte sa défense
            }

            else if(lEnemy_Luck > 0){
                lHeuristicCommand = engine::SPELL_2; // Cherche à baisser la luck adverse
            }

            else { 
                lHeuristicCommand = engine::ATTACK_1; //On privilégie une attaque de dégats
            }


            break;

        case ESC: // Magicien
        /**
         * @brief 11/12/21 : Problème d'équilibrage sur ce perso, à revoir ses capacités. Issue #59
         * 
         */
            lHeuristicCommand = engine::ATTACK_1; 
            break;

        case AUDENCIA: // Support/soin

            if(lAlivePlayer >1 && lPlayerTurn == PLAYER_TURN){ // Si il y a encore plus d'un character dans la team player
                lHeuristicCommand = engine::SPELL_2; // Buff pour la team
            }

            else if(lPlayer_LifePoints < (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est < à 60%
                lHeuristicCommand = engine::SPELL_1; // On privilégie la montée de sa vie
           
            }

            else{ 
                lHeuristicCommand = engine::ATTACK_1; //On privilégie une attaque de dégats
            }
            break;

        }

        SetStatusCommand(lHeuristicCommand);
    }


    void ai::HeuristicAI::SetStatusCommand(engine::CommandID rNewCommand){
        mInputCommand = rNewCommand;
        NotifyNewAICommand();
    }

    engine::CommandID ai::HeuristicAI::GetStatusCommand() const{
        return this->mInputCommand;
    }

}