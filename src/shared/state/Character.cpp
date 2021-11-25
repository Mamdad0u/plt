#include <state/Character.h>  // Included from library shared_static
#include "Character.h"
#include <fstream>
#include <jsoncpp/json/json.h>
#include "jsoncpp/json/value.h"
#include <iostream>
namespace state {


state::Character::Character(Major rCharacterMajor, CharacterStatus rCharacterStatus, std::string rCharacterName) {

    this->mCharacterName = rCharacterName;
    this->mCharacterMajor = rCharacterMajor;
    this->mCharacterStatus = rCharacterStatus;
}


void state::Character::SetCharacterStats(StatsName rStatsName, int rValue) {
    switch (rStatsName)
    {
    case MAX_LIFE_POINTS:
        mCharacterStats.Set_max_life_points(rValue);
        break;

    case LIFE_POINTS:
        mCharacterStats.Set_life_points(rValue);
        break;

    case ATTACK:
        mCharacterStats.Set_attack(rValue);
        break;

    case POWER:
        mCharacterStats.Set_power(rValue);
        break;
    
    case DEFENSE:
        mCharacterStats.Set_defense(rValue);
        break;

    case LUCK:
        mCharacterStats.Set_luck(rValue);
        break;
        
    default:
        break;
    }  
}

int state::Character::GetCharacterStats(StatsName rStatsName) {
   
   /*
   ifstream ifs("res/JSON_files/statistics.json");
    Json::Reader reader;
    Json::Value obj;

    reader.parse(ifs,obj);
    */

    switch (rStatsName)
    {
    case MAX_LIFE_POINTS:
        return this->mCharacterStats.Get_max_life_points();
        //return obj["Statistics"][this->mCharacterOption]["PV"];
        break;

    case LIFE_POINTS:
        return this->mCharacterStats.Get_life_points();
        break;

    case ATTACK:
        return this->mCharacterStats.Get_attack();
        //return obj["Statistics"][this->mCharacterOption]["ATTACK"];
        break;

    case POWER:
        return this->mCharacterStats.Get_power();
        //return obj["Statistics"][this->mCharacterOption]["POWER"];
        break;
    
    case DEFENSE:
        return this->mCharacterStats.Get_defense();
        //return obj["Statistics"][this->mCharacterOption]["DEFENSE"];
        break;

    case LUCK:
        return this->mCharacterStats.Get_luck();
        //return obj["Statistics"][this->mCharacterOption]["LUCK"];
        break;
        
    default:
        break;
    } 

    



}


Major state::Character::GetMajor() {
    return this->mCharacterMajor;
}


void state::Character::SetCharacterStatus(CharacterStatus rNewStatus){
    this->mCharacterStatus = rNewStatus;

}

CharacterStatus state::Character::GetCharacterStatus(){

    return this->mCharacterStatus;

}

/*
Options state::Character::GetCharacterOption() {

    return this->mCharacterOption;

}
*/



}