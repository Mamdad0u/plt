#include <state/Action.h>  // Included from library shared_static
#include "Action.h"
namespace state {

    void state::Action::SetDamage(int rDamageValue){
        this->mDamage = rDamageValue;
    }
    
    int state::Action::GetDamage(){
        return this->mDamage;
    }


}