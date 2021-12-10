#include <state/State.h>  // Included from library shared_static
#include "State.h"
#include <iostream>
#include <assert.h> 

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
    mActivePlayerCharacter = 0;
}



void State::MoveNextCombat() {
    this->mCombatNumber++;
}

void State::MoveNextTurn(){
    this->mTurn++;
}

int State::GetTurn(){
    return this->mTurn;
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
    cout << endl;
    cout << "************ IT IS NOW " << mPlayerStatusStringMap[mPlayerStatus] << " ! ************" << endl;
}


void State::GoToNextArena() {
    this->mArenaNumber++;
}

void State::AddPlayerCharacter(CharacterName rNewCharacter) {
    Character lNewCharacter(rNewCharacter);
    JSON.JSON_Configure_Character(lNewCharacter);
    
    
    mPlayersCharacters.push_back(lNewCharacter);
    cout << lNewCharacter.GetName() << " has joined the player team !" << endl;
}

void State::AddEnemyCharacter(CharacterName rNewCharacter){
    Character lNewCharacter(rNewCharacter);
    JSON.JSON_Configure_Character(lNewCharacter);
    
    if(GetEnemyRosterSize()==1){
        mEnemyCharacters.pop_back();
    }
    
    mEnemyCharacters.push_back(lNewCharacter);
    cout << lNewCharacter.GetName() << " has joined the enemy team !" << endl;

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
    int lIndex = 0;
    if(mActivePlayerCharacter == mPlayersCharacters.size()-1){
        mActivePlayerCharacter = 0;
    }
    else{
        mActivePlayerCharacter++;
    }

    if( mPlayersCharacters[mActivePlayerCharacter].GetCharacterStatus() == DEAD){ // If New active character is dead
        for(int lIndex = mActivePlayerCharacter; mPlayersCharacters[lIndex].GetCharacterStatus() == DEAD; lIndex++);
        mActivePlayerCharacter = lIndex;
    }
    
    


/*     if((mActivePlayerCharacter < mPlayersCharacters.size()-1) && (mActivePlayerCharacter < MAX_CHARACTER)){
        mActivePlayerCharacter++;

        if((mPlayersCharacters[mActivePlayerCharacter].GetCharacterStatus() == DEAD)  && mActivePlayerCharacter < mPlayersCharacters.size()){
            mActivePlayerCharacter++;
        }

        else if((mActivePlayerCharacter == mPlayersCharacters.size()) || (mPlayersCharacters[mActivePlayerCharacter].GetCharacterStatus() == DEAD)){
            mActivePlayerCharacter = 0;
        }
    }

    else{
        mActivePlayerCharacter = 0;
    }
 */
}

void State::SetAlivePlayer(){

    for(int i=0;i<mPlayersCharacters.size();i++){
        if((mPlayersCharacters[i].GetCharacterStats(LIFE_POINTS) == 0) && (mPlayersCharacters[i].GetCharacterStatus() != DEAD)){
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

int State::GetEnemyRosterSize(){
    return this->mEnemyCharacters.size();
}



}