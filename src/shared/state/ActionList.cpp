#include <state/ActionList.h>  // Included from library shared_static
#include "ActionList.h"
namespace state {
    state::ActionList::ActionList(){
        mAttackList.reserve(2);
        mSpellList.reserve(2);

    }

    Action* state::ActionList::GetAttack (int rAttackNumber){

        Action* lReturnAttack = nullptr;

        lReturnAttack = &mAttackList[rAttackNumber];
        return lReturnAttack;

    }

    void state::ActionList::SetAttack(int rAttackNumber, int rDamageValue){
        this->mAttackList[rAttackNumber].SetDamage(rDamageValue);
    }

    void state::ActionList::SetSpell(int rSpellNumber, int rDamageValue){
        this->mSpellList[rSpellNumber].SetDamage(rDamageValue);
    }

    void state::ActionList::SetAttackBuff(int rAttackNumber, StatsName rStatBuffname, int rStatBuffValue, bool rBeneficial){
        this->mAttackList[rAttackNumber].SetStatBuffName(rStatBuffname);
        this->mAttackList[rAttackNumber].SetStatBuffValue(rStatBuffValue);
        this->mAttackList[rAttackNumber].SetBuffBeneficial(rBeneficial);



    }


    


}