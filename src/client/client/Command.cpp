#include <client/Command.h>  // Included from library shared_static
#include "Command.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

using namespace state;

namespace client {

    client::Command::Command(){
        srand(time(NULL));

    }

    float client::Command::ComputeWeakAndStrength(state::Major rAttackerMajor, state::Major rVictimMajor){
        
        switch(rAttackerMajor){
            case ELEC:
                switch (rVictimMajor)
                {
                case ELEC:
                    return NEUTRAL;

                case INFO:
                    return NEUTRAL;

                case AUTO:
                    return WEAK;

                case SIGNAL:
                    return STRENGTH;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;

                }
                break;
            
            case INFO:
                switch (rVictimMajor)
                {
                case ELEC:
                    return NEUTRAL;

                case INFO:
                    return NEUTRAL;

                case AUTO:
                    return STRENGTH;

                case SIGNAL:
                    return WEAK;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;
                }
                break;

            case AUTO:
                switch (rVictimMajor)
                {
                case ELEC:
                    return STRENGTH;

                case INFO:
                    return WEAK;

                case AUTO:
                    return NEUTRAL;

                case SIGNAL:
                    return NEUTRAL;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;

                }
                break;

            case SIGNAL:
                switch (rVictimMajor)
                {
                case ELEC:
                    return WEAK;

                case INFO:
                    return STRENGTH;

                case AUTO:
                    return NEUTRAL;

                case SIGNAL:
                    return NEUTRAL;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;
                }
                break;

            case SCIENCES_HUMAINES:
                switch (rVictimMajor)
                {
                case SCIENCES_HUMAINES:
                    return STRENGTH;
                

                default: // All other major
                    return NEUTRAL;
                }
                break;
        }
        
    }

    float client::Command::ComputePVLost(state::Character &rAttacker, state::Character &rVictim, CommandID rActionMade){
        float lCoeffMajor;
        int lCriticalHit;
        int lAttackDamage;
        int lVictimDefense;
        int lAttackStat;
        float lPVLost;
        const float lMagicCoefficiant = 0.44;
        Action* lActionGot = nullptr;

        /*Récupération du type d'action*/
        switch (rActionMade)
        {
        case ATTACK_1:
            lActionGot = rAttacker.MakeAction(state::ATTACK_1);
            break;
        
        case ATTACK_2:
            lActionGot = rAttacker.MakeAction(state::ATTACK_2);
            break;

        case SPELL_1:
            lActionGot = rAttacker.MakeAction(state::SPELL_1);
            break;

        case SPELL_2:
            lActionGot = rAttacker.MakeAction(state::SPELL_2);
            break;

        }

        /*Calcul*/
        lCoeffMajor = ComputeWeakAndStrength(rAttacker.GetMajor(), rVictim.GetMajor()); // Calcul avantage/désavantage majeur
        lCriticalHit = ComputeCriticalHit(rAttacker.GetCharacterStats(StatsName::LUCK)); // Calcul coup critique
        lAttackDamage = lActionGot->GetDamage(); // Dégâts de l'attaque
        lVictimDefense = rVictim.GetCharacterStats(StatsName::DEFENSE); // Défense de la victime
        lAttackStat = rAttacker.GetCharacterStats(StatsName::ATTACK); // Attaque de l'attaquant
       
       
        lPVLost = ((lCoeffMajor * lCriticalHit * lAttackDamage * lAttackStat) / lVictimDefense) * lMagicCoefficiant;
        cout << rAttacker.GetName() << " inflicted " << lPVLost << " on " << rVictim.GetName() << endl;; 
        return lPVLost;
        


    }


    float client::Command::ComputeCriticalHit(int rCharacterLuck){
        int lRandomResult;
        int lCriticalHit;
        
        lRandomResult = rand() % 100 + 1;

        if(lRandomResult <= rCharacterLuck){
            lCriticalHit = 2;
            cout << "Critical hit !" << endl;
        }
        else{
            lCriticalHit = 1;
            cout << "No critical hit" << endl;
        }

        return lCriticalHit;

    }
}