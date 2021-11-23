#include <state/ActionList.h>  // Included from library shared_static
#include "ActionList.h"
namespace state {
    state::ActionList::ActionList(){
        mAttackList.reserve(3);
        mSpellList.reserve(3);

    }

    Action* state::ActionList::GetAttack (int rAttackNumber){

        Action* lReturnAttack = nullptr;

        lReturnAttack = &mAttackList[rAttackNumber];
        return lReturnAttack;

    }

    Action* state::ActionList::GetSpell (int rSpellNumber){
        Action* lReturnSpell = nullptr;

        lReturnSpell = &mAttackList[rSpellNumber];
        return lReturnSpell;
    }

    void state::ActionList::SetAttack(int rAttackNumber, int rDamageValue, StatsName rStatsBuffName, int rStatsBuffValue, bool rBeneficial){
        this->mAttackList[rAttackNumber].SetDamage(rDamageValue);
        this->mAttackList[rAttackNumber].SetStatBuffName(rStatsBuffName);
        this->mAttackList[rAttackNumber].SetStatBuffValue(rStatsBuffValue);
        this->mAttackList[rAttackNumber].SetBuffBeneficial(rBeneficial);
    }

    void state::ActionList::SetSpell(int rSpellNumber, int rDamageValue, StatsName rStatsBuffName, int rStatsBuffValue, bool rBeneficial){
        this->mSpellList[rSpellNumber].SetDamage(rDamageValue);
        this->mSpellList[rSpellNumber].SetStatBuffName(rStatsBuffName);
        this->mSpellList[rSpellNumber].SetStatBuffValue(rStatsBuffValue);
        this->mSpellList[rSpellNumber].SetBuffBeneficial(rBeneficial);
    }


    


}