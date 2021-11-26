#include <state/ActionList.h>  // Included from library shared_static
#include "ActionList.h"
namespace state {
    state::ActionList::ActionList(){
        Action lNewAction;

        mAttackList.reserve(3);
        mSpellList.reserve(3);

        for(int i=0;i<MAX_CHARACTER_ACTION;i++){
            mAttackList.push_back(lNewAction);
            mSpellList.push_back(lNewAction);
        }
        
    }

    Action* state::ActionList::GetAttack (int rAttackNumber){

        Action* lReturnAttack = nullptr;

        lReturnAttack = &mAttackList[rAttackNumber-1];
        return lReturnAttack;

    }

    Action* state::ActionList::GetSpell (int rSpellNumber){
        Action* lReturnSpell = nullptr;

        lReturnSpell = &mAttackList[rSpellNumber-1];
        return lReturnSpell;
    }

    void state::ActionList::SetAttack(int rAttackNumber, int rDamageValue, StatsName rStatsBuffName, int rStatsBuffValue, bool rBeneficial){
        this->mAttackList[rAttackNumber-1].SetDamage(rDamageValue);
        this->mAttackList[rAttackNumber-1].SetStatBuffName(rStatsBuffName);
        this->mAttackList[rAttackNumber-1].SetStatBuffValue(rStatsBuffValue);
        this->mAttackList[rAttackNumber-1].SetBuffBeneficial(rBeneficial);
    }

    void state::ActionList::SetSpell(int rSpellNumber, int rDamageValue, StatsName rStatsBuffName, int rStatsBuffValue, bool rBeneficial){
        this->mSpellList[rSpellNumber-1].SetDamage(rDamageValue);
        this->mSpellList[rSpellNumber-1].SetStatBuffName(rStatsBuffName);
        this->mSpellList[rSpellNumber-1].SetStatBuffValue(rStatsBuffValue);
        this->mSpellList[rSpellNumber-1].SetBuffBeneficial(rBeneficial);
    }


    


}