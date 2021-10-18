#include <state/CharacterStatus.h>  // Included from library shared_static
#include "CharacterStatus.h"
namespace state {


state::CharacterStatus::CharacterStatus() {
    
}

void state::CharacterStatus::SetIsAlive(bool rValue) {
    this->mIsAlive = rValue;
}

void state::CharacterStatus::SetIsPlayable(bool rValue) {
    this->mIsPlayable = rValue;
}

bool state::CharacterStatus::GetIsAlive() {
    return this->mIsAlive;
}

bool state::CharacterStatus::GetIsPlayable() {
    return this->mIsPlayable;
}

}