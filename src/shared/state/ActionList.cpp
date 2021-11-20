#include <state/ActionList.h>  // Included from library shared_static
#include "ActionList.h"
namespace state {
    state::ActionList::ActionList(){
        mAttackList.reserve(2);
        mSpellList.reserve(2);

    }

    Action* state::ActionList::GetAction (int rAttackNumber){

        Action* lReturnAttack = nullptr;

        lReturnAttack = &mAttackList[rAttackNumber];
        return lReturnAttack;

    }

    


}