#include <state/State.h>  // Included from library shared_static
#include "State.h"
namespace state {
    


State::State(CombatStatus rCombatStatus) {
    this->mCombatStatus = rCombatStatus;
    mPlayersCharacters.reserve(MAX_CHARACTER);
}

std::vector<Character> State::GetCharacter() {
    
}

void State::MoveNextCombat() {
    this->mCombatNumber++;
}

int State::GetCombatNumber(){
    return this->mCombatNumber;
}

void State::SetCombatState(CombatStatus rNewCombatState) {
    this->mCombatStatus = rNewCombatState;
}

CombatStatus State::GetCombatState(){
    return this->mCombatStatus;
}

Player_Status State::GetPlayerStatus(){
    return this->mPlayerStatus;
}

void State::InitializeEnemyCharactersList() {
    
}

void State::BeginFight() {
    
}

void State::BeginRandomEvent() {
    
}

void State::GotoNextArena() {
    
}

void State::AddPlayerCharacter(Character rNewCharacter) {
    mPlayersCharacters.push_back(rNewCharacter);
}

}