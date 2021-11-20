#include <state/Action.h>  // Included from library shared_static
#include "Action.h"
namespace state {
    state::Action::Action(){
        mAttackList.reserve(2);
        mSpellList.reserve(2);

    }

    Attack* state::Action::GetAttack(int rAttackNumber){

        Attack* lReturnAttack = nullptr;

        lReturnAttack = &mAttackList[rAttackNumber];
        return lReturnAttack;

    }

    


}