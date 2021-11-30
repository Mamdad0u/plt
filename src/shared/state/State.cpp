#include <state/State.h>  // Included from library shared_static
#include "State.h"
#include <iostream>

using namespace std;

namespace state {
    


State::State(CombatStatus rCombatStatus, Player_Status rPlayerStatus) {
    
    mPlayerStatusStringMap[PLAYER_TURN] = "PLAYER TURN";
    mPlayerStatusStringMap[IA_TURN] = "IA TURN";
    
    mCombatStatusStringMap[IN_COMBAT] = "IN_COMBAT";
    mCombatStatusStringMap[OUT_COMBAT] = "OUT_COMBAT";
    mCombatStatusStringMap[GAME_OVER] = "GAME_OVER";

    this->mCombatStatus = rCombatStatus;
    this->mPlayerStatus = rPlayerStatus;
    mPlayersCharacters.reserve(MAX_CHARACTER);
    mEnemyCharacters.reserve(MAX_ENEMY_NUMBER);
}



void State::MoveNextCombat() {
    this->mCombatNumber++;
}

int State::GetCombatNumber(){
    return this->mCombatNumber;
}

void State::SetCombatState(CombatStatus rNewCombatState) {
    this->mCombatStatus = rNewCombatState;
    cout << "Game is now in " << mCombatStatusStringMap[mCombatStatus] << " state" << endl;;
}

CombatStatus State::GetCombatState(){
    return this->mCombatStatus;
}

Player_Status State::GetPlayerStatus(){
    return this->mPlayerStatus;
}

void State::SetPlayerStatus(Player_Status rNewPlayerStatus){

    this->mPlayerStatus = rNewPlayerStatus;
    cout << "************ IT IS NOW " << mPlayerStatusStringMap[mPlayerStatus] << " ! ************" << endl;
}


void State::GoToNextArena() {
    this->mArenaNumber++;
}

void State::AddPlayerCharacter(Character& rNewCharacter) {

    mPlayersCharacters.push_back(rNewCharacter);
    cout << rNewCharacter.GetName() << " has joined the player team !" << endl;
}

void State::AddEnemyCharacter(Character& rNewCharacter){
    mEnemyCharacters.push_back(rNewCharacter);

}

Character* State::GetActivePlayerCharacter(){
    
    for(int lIndex=mActivePlayerCharacter; lIndex<MAX_CHARACTER; lIndex++){
        if((mPlayersCharacters[lIndex].GetCharacterStatus() != DEAD)){
            return &this->mPlayersCharacters[lIndex]; //Returning 1st character not dead since the last one active
        }
    }
    
}

Character* State::GetEnemyCharacter(){
    return &this->mEnemyCharacters[0];


}

void State::MoveActivePlayer(){
    if(mActivePlayerCharacter < MAX_CHARACTER){
        mActivePlayerCharacter++;

        if((mPlayersCharacters[mActivePlayerCharacter].GetCharacterStatus() != DEAD)  && mActivePlayerCharacter < MAX_CHARACTER){
            mActivePlayerCharacter++;
        }

        else{
            mActivePlayerCharacter = 0;
        }
    }

    else{
        mActivePlayerCharacter = 0;
    }

}

void State::SetAlivePlayer(){

    for(int i=0;i<mPlayersCharacters.size();i++){
        if(mPlayersCharacters[i].GetCharacterStats(LIFE_POINTS) == 0){
            mPlayersCharacters[i].SetCharacterStatus(DEAD);
        }
    }
}


void State::SetAliveEnemy(){

    for(int i=0;i<mEnemyCharacters.size();i++){
        if(mEnemyCharacters[i].GetCharacterStats(LIFE_POINTS) == 0){
            mEnemyCharacters[i].SetCharacterStatus(DEAD);
        }
    }
}

bool State::GetAlivePlayer(){
    int lDeadCharacter = 0;

    for(int i=0;i<mPlayersCharacters.size();i++){
        if(mPlayersCharacters[i].GetCharacterStatus() == DEAD){
            lDeadCharacter++;
        }
    }

    if(lDeadCharacter == mPlayersCharacters.size()){
        return false;
    }

    return true;

}

bool State::GetAliveEnemy(){
    int lDeadCharacter = 0;

    for(int i=0;i<mEnemyCharacters.size();i++){
        if(mEnemyCharacters[i].GetCharacterStatus() == DEAD){
            lDeadCharacter++;
        }
    }

    if(lDeadCharacter == mEnemyCharacters.size()){
        return false;
    }

    return true;
}

int State::GetPlayerRosterSize(){
    return this->mPlayersCharacters.size();

}



}