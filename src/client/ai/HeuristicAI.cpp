#include <ai/HeuristicAI.h>  // Included from library shared_static
#include "HeuristicAI.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace client;
using namespace state;

namespace ai {


    ai::HeuristicAI::HeuristicAI(){

    }



    client::CommandID ai::HeuristicAI::GenerateHeuristicCommand(){
        const float lLife_threshold = 0.8f;
        CommandID lHeuristicCommand;
        std::list<EngineObserver*>::iterator lRunningEngine;
        lRunningEngine = this->mEngineObserverList.begin(); // Récupération des paramètres de l'engine 
        State lGameStatus = (*lRunningEngine)->mCurrentState; // Récupération de l'état du jeu depuis l'engine
        Character* lActiveCharacter; // Character actif joueur durant ce tour
        Character* lActiveEnemyCharacter;
        CharacterName lSpeciality;
        state::Player_Status lPlayerTurn = lGameStatus.GetPlayerStatus();

        const int lMax_luck = 25;
        int lPlayer_RosterSize = lGameStatus.GetPlayerRosterSize();

        int lEnemy_MaxLifePoints = 0; 
        int lEnemy_LifePoints = 0;
        int lEnemy_Luck = 0;
        int lEnemy_Defense = 0;

        int lPlayer_MaxLifePoints = 0; 
        int lPlayer_LifePoints = 0;
        int lPlayer_Luck = 0;
        int lPlayer_Defense = 0;

        if(lPlayerTurn == PLAYER_TURN){ // Si c'est le tour de l'IA joueur de jouer
            lActiveCharacter = lGameStatus.GetActivePlayerCharacter(); // Récupération du character actif de l'IA joueur en train d'être joué
            lActiveEnemyCharacter = lGameStatus.GetEnemyCharacter();
        }

        else if((lPlayerTurn == IA_TURN)){ //  Si c'est le tour de l'IA enemy de jouer
            lActiveCharacter = lGameStatus.GetEnemyCharacter(); // Récupération de son character
            lActiveEnemyCharacter = lGameStatus.GetActivePlayerCharacter();
        }
        lSpeciality = lActiveCharacter->GetCharacterNameNumber();

        lEnemy_MaxLifePoints = lActiveEnemyCharacter->GetCharacterStats(MAX_LIFE_POINTS);
        lEnemy_LifePoints = lActiveEnemyCharacter->GetCharacterStats(LIFE_POINTS);
        lEnemy_Luck = lActiveEnemyCharacter->GetCharacterStats(LUCK);
        lEnemy_Defense = lActiveEnemyCharacter->GetCharacterStats(DEFENSE);

        lPlayer_MaxLifePoints = lActiveCharacter->GetCharacterStats(MAX_LIFE_POINTS);
        lPlayer_LifePoints = lActiveCharacter->GetCharacterStats(LIFE_POINTS);
        lPlayer_Luck = lActiveCharacter->GetCharacterStats(LUCK);
        
        /**
         * @brief Les lignes suivantes détaillent le fonctionnement du choix d'une commande selon des heuristiques
         * 
         */

        switch (lSpeciality)
        {
        case IS: // Polyvalent
            if(lEnemy_LifePoints < (lLife_threshold * lEnemy_MaxLifePoints)){ // Si la vie du character adverse est < à 60%
                lHeuristicCommand = client::ATTACK_1; //On privilégie une attaque de dégats
            }

            else{ // Sinon on privilégie la montée de la stat d'attaque
                lHeuristicCommand = client::SPELL_2;
            }
            break;
        
        case SIA: // Magicien
            
            if(lPlayer_Luck < lMax_luck){ // Priorité : augmenter sa luck
                lHeuristicCommand = client::SPELL_2;
            }

            else if(lEnemy_Luck > 0){ // Sinon on cherche à baisser sa luck
                lHeuristicCommand = client::ATTACK_1;
            }

            else{ 
                lHeuristicCommand = client::SPELL_1; //On privilégie une attaque de dégats
            }

            break;

        case RT: // Attaquant
        
            if(lEnemy_LifePoints < (lLife_threshold * lEnemy_MaxLifePoints)){ // Si la vie du character adverse est < à 60%
                lHeuristicCommand = client::ATTACK_1; //On privilégie une attaque de dégats
            }

            else if(lEnemy_Defense > 0){ // Sinon on cherche à baisser sa defense
                lHeuristicCommand = client::SPELL_1;
            }

            else{ // Et enfin à augmenter la sienne
                lHeuristicCommand = client::ATTACK_2;
            }

            break;

        case MSC: // Tank

            if(lPlayer_RosterSize >1 && lPlayerTurn == PLAYER_TURN){ // Si il y a encore plus d'un character dans la team player
                lHeuristicCommand = client::SPELL_1; // buff de LP pour la team
            }
            else if(lPlayer_LifePoints < (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est < à 60%
                lHeuristicCommand = client::ATTACK_2; // On privilégie la montée de sa vie
           
            }

            else{ // Sinon 
                lHeuristicCommand = client::ATTACK_1; //On privilégie une attaque de dégats
            }

            break;

        case AEI: // Attaquant
            if(lEnemy_LifePoints < (lLife_threshold * lEnemy_MaxLifePoints)){ // Si la vie du character adverse est < à 60%
                lHeuristicCommand = client::ATTACK_1; //On privilégie une attaque de dégats
            }

            else if(lPlayer_LifePoints > (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est > à 60%
                lHeuristicCommand = client::ATTACK_2; //On privilégie une grosse attaque de dégats qui lui fait perdre de la vie 
            }

            else{
                lHeuristicCommand = client::SPELL_1; // Sinon buff d'attaque pour l'équipe
            }
            break;

        case EVE: // Support/soin

            if(lPlayer_RosterSize >1 && lPlayerTurn == PLAYER_TURN){ // Si il y a encore plus d'un character dans la team player
                lHeuristicCommand = client::SPELL_2;
            }

            else if(lPlayer_LifePoints < (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est < à 60%
                lHeuristicCommand = client::SPELL_1; // On privilégie la montée de sa vie
           
            }

            else{ // Sinon on privilégie une attaque de dégats
                lHeuristicCommand = client::ATTACK_1; 
            }
            break;

        case ESE: // Tank
            if(lEnemy_LifePoints < (lLife_threshold * lEnemy_MaxLifePoints)){ // Si la vie du character adverse est < à 60%
                lHeuristicCommand = client::ATTACK_1; //On privilégie une attaque de dégats
            }

            else if(lEnemy_Luck > 0){
                lHeuristicCommand = client::SPELL_1; // Cherche à baisser la luck adverse
            }

            else{
                lHeuristicCommand = client::ATTACK_2; // Sinon il monte sa défense
            }
            break;

        case ESC: // Magicien
        /**
         * @brief 11/12/21 : Problème d'équilibrage sur ce perso, à revoir ses capacités. Issue #59
         * 
         */
            lHeuristicCommand = client::ATTACK_1; 
            break;

        case AUDENCIA: // Support/soin

            if(lPlayer_RosterSize >1 && lPlayerTurn == PLAYER_TURN){ // Si il y a encore plus d'un character dans la team player
                lHeuristicCommand = client::SPELL_2; // Buff pour la team
            }

            else if(lPlayer_LifePoints < (lLife_threshold * lPlayer_MaxLifePoints)){ // Si la vie du character joueur est < à 60%
                lHeuristicCommand = client::SPELL_1; // On privilégie la montée de sa vie
           
            }

            else{ 
                lHeuristicCommand = client::ATTACK_1; //On privilégie une attaque de dégats
            }
            break;

        }

        SetStatusCommand(lHeuristicCommand);
    }


    void ai::HeuristicAI::SetStatusCommand(client::CommandID rNewCommand){
        mInputCommand = rNewCommand;
        NotifyNewAICommand();
    }

    client::CommandID ai::HeuristicAI::GetStatusCommand() const{
        return this->mInputCommand;
    }

}