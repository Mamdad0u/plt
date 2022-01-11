#include "Character.h"
#include <iostream>
#include <state/Character.h> // Included from library shared_static

using namespace std;

namespace state {

state::Character::Character() {
  mCharacterStatusStringMap[ALIVE] = "ALIVE";
  mCharacterStatusStringMap[DEAD] = "DEAD";
}

state::Character::Character(CharacterName rCharacterName) {
    mCharacterStatusStringMap[ALIVE] = "ALIVE";
    mCharacterStatusStringMap[DEAD] = "DEAD";
    
    mCharacterNameMap[IS] = "IS";
    mCharacterNameMap[SIA] = "SIA";
    mCharacterNameMap[EVE] = "EVE";
    mCharacterNameMap[MSC] = "MSC";
    mCharacterNameMap[ESE] = "ESE";
    mCharacterNameMap[AEI] = "AEI";
    mCharacterNameMap[RT] = "RT";
    mCharacterNameMap[ESC] = "ESC";
    mCharacterNameMap[AUDENCIA] = "AUDENCIA";

    this->mCharacterNameNumber = rCharacterName;
    this->mName = mCharacterNameMap[rCharacterName];
    
    

    switch (rCharacterName)
    {
    case IS:
        this->mCharacterMajor = INFO;
        break;

    case SIA:
        this->mCharacterMajor = SIGNAL;
        break;

    case EVE:
        this->mCharacterMajor = SIGNAL;
        break;

    case MSC:
        this->mCharacterMajor = AUTO;
        break;

    case ESE:
        this->mCharacterMajor = ELEC;
        break;

    case AEI:
        this->mCharacterMajor = AUTO;
        break;

    case RT:
        this->mCharacterMajor = SIGNAL;
        break;

    case ESC:
        this->mCharacterMajor = ELEC;
        break;

    case AUDENCIA:
        this->mCharacterMajor = SCIENCES_HUMAINES;
        break;
        


    }

}
CharacterName state::Character::GetCharacterNameNumber(){
    return this->mCharacterNameNumber;
}

void state::Character::SetCharacterStats(StatsName rStatsName, int rValue) {
  switch (rStatsName) {
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
  switch (rStatsName) {
  case MAX_LIFE_POINTS:
    return this->mCharacterStats.Get_max_life_points();

  case LIFE_POINTS:
    return this->mCharacterStats.Get_life_points();

  case ATTACK:
    return this->mCharacterStats.Get_attack();

  case POWER:
    return this->mCharacterStats.Get_power();

  case DEFENSE:
    return this->mCharacterStats.Get_defense();

  case LUCK:
    return this->mCharacterStats.Get_luck();

  default:
    return -1;
  }
}

void state::Character::SetCharacterAction(ActionListCommand rAction, int rDamageValue, StatsName rStatsBuffName, int rStatsBuffValue, BuffType rBeneficial){
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

ActionList* state::Character::GetActionList(){
    return &mCharacterAction;
}

Major state::Character::GetMajor() { 
  return this->mCharacterMajor; 
  }

void state::Character::SetCharacterStatus(CharacterStatus rNewStatus) {
  if(mDebugInfo){
    cout << this->mName << " is now " << mCharacterStatusStringMap[rNewStatus] << endl;
  }
  
  this->mCharacterStatus = rNewStatus;
}

CharacterStatus state::Character::GetCharacterStatus() {

  return this->mCharacterStatus;
}

Action *state::Character::GetAction(ActionListCommand rActionType) {
  switch (rActionType) {
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

} // namespace state