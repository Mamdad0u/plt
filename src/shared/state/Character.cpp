#include "Character.h"
#include <iostream>
#include <state/Character.h> // Included from library shared_static

using namespace std;

namespace state {

state::Character::Character() {
  mCharacterStatusStringMap[ALIVE] = "ALIVE";
  mCharacterStatusStringMap[DEAD] = "DEAD";
}

state::Character::Character(std::string rCharacterName, Major rCharacterMajor,
                            CharacterStatus rCharacterStatus) {

  this->mName = rCharacterName;
  this->mCharacterMajor = rCharacterMajor;
  this->mCharacterStatus = rCharacterStatus;

  mCharacterStatusStringMap[ALIVE] = "ALIVE";
  mCharacterStatusStringMap[DEAD] = "DEAD";
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

void state::Character::SetCharacterAction(ActionListCommand rAction,
                                          int rDamageValue,
                                          StatsName rStatsBuffName,
                                          int rStatsBuffValue,
                                          bool rBeneficial) {
  switch (rAction) {
  case ATTACK_1:
    mCharacterAction.SetAttack(1, rDamageValue, rStatsBuffName, rStatsBuffValue,
                               rBeneficial);
    break;

  case ATTACK_2:
    mCharacterAction.SetAttack(2, rDamageValue, rStatsBuffName, rStatsBuffValue,
                               rBeneficial);
    break;

  case SPELL_1:
    mCharacterAction.SetSpell(1, rDamageValue, rStatsBuffName, rStatsBuffValue,
                              rBeneficial);
    break;

  case SPELL_2:
    mCharacterAction.SetSpell(2, rDamageValue, rStatsBuffName, rStatsBuffValue,
                              rBeneficial);
    break;
  }
}

Major state::Character::GetMajor() { return this->mCharacterMajor; }

void state::Character::SetCharacterStatus(CharacterStatus rNewStatus) {
  cout << this->mName << " is now " << mCharacterStatusStringMap[rNewStatus]
       << endl;
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