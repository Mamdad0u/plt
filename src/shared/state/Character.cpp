#include <state/Character.h>  // Included from library shared_static
#include "Character.h"
#include <fstream>
#include <jsoncpp/json/json.h>
#include "jsoncpp/json/value.h"
#include <iostream>
namespace state {


state::Character::Character(std::string rCharacterName, Major rCharacterMajor, CharacterStatus rCharacterStatus) {

    this->mName = rCharacterName;
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

void state::Character::SetCharacterAction(ActionListCommand rAction, int rDamageValue, StatsName rStatsBuffName, int rStatsBuffValue, bool rBeneficial){
    switch (rAction)
    {
    case ATTACK_1:
        mCharacterAction.SetAttack(1, rDamageValue, rStatsBuffName, rStatsBuffValue, rBeneficial);
        break;
    
    case ATTACK_2:
        mCharacterAction.SetAttack(2, rDamageValue, rStatsBuffName, rStatsBuffValue, rBeneficial);
        break;

    case SPELL_1:
        mCharacterAction.SetSpell(1, rDamageValue, rStatsBuffName, rStatsBuffValue, rBeneficial);
        break;

    case SPELL_2:
        mCharacterAction.SetSpell(2, rDamageValue, rStatsBuffName, rStatsBuffValue, rBeneficial);
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

Action* state::Character::GetAction(ActionListCommand rActionType){
    switch (rActionType)
    {
    case ATTACK_1:
        return this->mCharacterAction.GetAttack(1);
        break;
    
    case ATTACK_2:
        return this->mCharacterAction.GetAttack(2);
        break;

    case SPELL_1:
        return this->mCharacterAction.GetSpell(1);
        break;
    
    case SPELL_2:
        return this->mCharacterAction.GetSpell(2);
        break;

    }

    
}



    





}