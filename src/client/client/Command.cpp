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
        mStatsNameMap[MAX_LIFE_POINTS] = "MAX_LIFE_POINTS";
        mStatsNameMap[LIFE_POINTS] = "LIFE_POINTS";
        mStatsNameMap[ATTACK] = "ATTACK";
        mStatsNameMap[POWER] = "POWER";
        mStatsNameMap[DEFENSE] = "DEFENSE";
        mStatsNameMap[LUCK] = "LUCK";

        mActionMap[ATTACK_1] = "ATTACK_1";
        mActionMap[ATTACK_2] = "ATTACK_2";
        mActionMap[SPELL_1] = "SPELL_1";
        mActionMap[SPELL_2] = "SPELL_2";
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

    float client::Command::ComputeAction(state::Character &rAttacker, state::Character &rVictim, CommandID rActionMade){
        float lCoeffMajor;
        int lCriticalHit;
        int lAttackDamage;
        int lVictimDefense;
        int lAttackStat;
        float lPVLost;
        const float lMagicCoefficiant = 0.44;
        int lBuffValue;
        StatsName lBuffName;
        bool lBeneficial;

        Action* lActionGot = nullptr;

        /*Récupération du type d'action*/
        switch (rActionMade)
        {
        case ATTACK_1:
            lActionGot = rAttacker.GetAction(state::ATTACK_1);
            break;
        
        case ATTACK_2:
            lActionGot = rAttacker.GetAction(state::ATTACK_2);
            break;

        case SPELL_1:
            lActionGot = rAttacker.GetAction(state::SPELL_1);
            break;

        case SPELL_2:
            lActionGot = rAttacker.GetAction(state::SPELL_2);
            break;

        }

        /*Calcul du nombre de PV perdu*/
        lCoeffMajor = ComputeWeakAndStrength(rAttacker.GetMajor(), rVictim.GetMajor()); // Calcul avantage/désavantage majeur
        lCriticalHit = ComputeCriticalHit(rAttacker.GetCharacterStats(StatsName::LUCK)); // Calcul coup critique
        lAttackDamage = lActionGot->GetDamage(); // Dégâts de l'attaque
        lVictimDefense = rVictim.GetCharacterStats(StatsName::DEFENSE); // Défense de la victime
        lAttackStat = rAttacker.GetCharacterStats(StatsName::ATTACK); // Attaque de l'attaquant

        lPVLost = ((lCoeffMajor * lCriticalHit * lAttackDamage * lAttackStat) / lVictimDefense) * lMagicCoefficiant;
        
        /*Application de la perte de PV*/
        
        
        cout  << mActionMap[rActionMade] << ": " << rAttacker.GetName() << " inflicted " << lPVLost << " PV lost on " << rVictim.GetName() << endl;
        
        /*Calcul de l'effet du buff*/
        lBuffValue = lActionGot->GetStatBuffValue();
        lBeneficial = lActionGot->GetBuffBeneficial();
        lBuffName = lActionGot->GetStatBuffName();

        if(!lBeneficial){ // Buff non bénéfique
            lBuffValue = lBuffValue * (-1);
            cout << mActionMap[rActionMade] << ": " << rAttacker.GetName() << " inflicted " << lBuffValue << " " <<mStatsNameMap[lBuffName] << " disadvantageous on " << rVictim.GetName() << endl;
        }
        else{ // Buff bénéfique
            cout << mActionMap[rActionMade] << ": " << rAttacker.GetName() << " got +" << lBuffValue << " " << mStatsNameMap[lBuffName] << " beneficial" << endl;
        }

        
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