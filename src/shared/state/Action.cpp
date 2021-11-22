#include <state/Action.h>  // Included from library shared_static
#include "Action.h"
namespace state {

    void state::Action::SetDamage(int rDamageValue){
        this->mDamage = rDamageValue;
    }
    
    int state::Action::GetDamage(){
        return this->mDamage;
    }

    StatsName state::Action::GetStatBuffName(){
        return this->mStatBuffName;
    }

    void state::Action::SetStatBuffName(StatsName rStatBuffName){
        mStatBuffName = rStatBuffName;
    }

    int state::Action::GetStatBuffValue(){
        return this->mStatBuffValue;
    }

    void state::Action::SetStatBuffValue(int rStatBuffValue){
        mStatBuffValue = rStatBuffValue;
    }

    void state::Action::SetBuffBeneficial(bool rValue){
        mBeneficial = rValue;
    }

    bool state::Action::GetBuffBeneficial(){
        return this->mBeneficial; 
    }

    

}