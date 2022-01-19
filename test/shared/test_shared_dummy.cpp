
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Exemple.h"
#include "../../src/shared/state/Character.h"
#include "../../src/shared/state/Element.h"
using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
    Exemple ex {};
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
  }

  {
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }
}

BOOST_AUTO_TEST_CASE(TestElement) 
{

  {
    Element UT_Element;
    BOOST_CHECK_EQUAL(UT_Element.GetName(), "Default name");
    BOOST_CHECK_EQUAL(UT_Element.getMX(), 0);
    BOOST_CHECK_EQUAL(UT_Element.getMY(), 0);


  }
}

BOOST_AUTO_TEST_CASE(TestAction){
  {
    Action UT_Action;

    BOOST_CHECK_EQUAL(UT_Action.GetDamage(),0);
    BOOST_CHECK_EQUAL(UT_Action.GetStatBuffValue(),0);

    UT_Action.SetDamage(42);
    UT_Action.SetStatBuffName(ATTACK);
    UT_Action.SetStatBuffValue(10);
    UT_Action.SetBuffBeneficial(BENEFICIAL_ATTACKER);

    BOOST_CHECK_EQUAL(UT_Action.GetDamage(),42);
    BOOST_CHECK_EQUAL(UT_Action.GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(UT_Action.GetStatBuffName(),ATTACK);
    BOOST_CHECK_EQUAL(UT_Action.GetBuffBeneficial(),BENEFICIAL_ATTACKER);    
  }
}

BOOST_AUTO_TEST_CASE(TestActionList){
  {
    ActionList UT_ActionList;

    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(1)->GetDamage(),0);
    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(2)->GetDamage(),0);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(1)->GetDamage(),0);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(2)->GetDamage(),0);

    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(1)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(2)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(1)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(2)->GetStatBuffValue(),0);

    UT_ActionList.SetAttack(1,42,ATTACK,10,BENEFICIAL_ATTACKER);
    UT_ActionList.SetAttack(2,44,LUCK,1,NEGATIVE_ATTACKER);

    UT_ActionList.SetSpell(1,50,POWER,20,BENEFICIAL_TEAM);
    UT_ActionList.SetSpell(2,45,LIFE_POINTS,2,NEGATIVE_ATTACKER);

    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(1)->GetDamage(),42);
    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(2)->GetDamage(),44);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(1)->GetDamage(),50);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(2)->GetDamage(),45);

    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(1)->GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(2)->GetStatBuffValue(),1);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(1)->GetStatBuffValue(),20);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(2)->GetStatBuffValue(),2);

    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(1)->GetStatBuffName(),ATTACK);
    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(2)->GetStatBuffName(),LUCK);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(1)->GetStatBuffName(),POWER);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(2)->GetStatBuffName(),LIFE_POINTS);

    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(1)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(UT_ActionList.GetAttack(2)->GetBuffBeneficial(),NEGATIVE_ATTACKER);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(1)->GetBuffBeneficial(),BENEFICIAL_TEAM);
    BOOST_CHECK_EQUAL(UT_ActionList.GetSpell(2)->GetBuffBeneficial(),NEGATIVE_ATTACKER);
   
  }
}

BOOST_AUTO_TEST_CASE(TestCharacter) 
{
  {
       
    Character UT_Character(ESE);

    UT_Character.SetCharacterStats(ATTACK, 15);
    UT_Character.SetCharacterStats(DEFENSE, 5);
    UT_Character.SetCharacterStats(LUCK, 10);
    UT_Character.SetCharacterStats(POWER, 12);
    UT_Character.SetCharacterStats(LIFE_POINTS, 42);
    UT_Character.SetCharacterStats(MAX_LIFE_POINTS, 150);
    
    BOOST_CHECK_EQUAL(UT_Character.GetMajor(), ELEC);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStatus(), ALIVE);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(ATTACK), 15);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(DEFENSE), 5); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(LUCK), 10); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(POWER), 12); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(LIFE_POINTS), 42); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(MAX_LIFE_POINTS), 150);

    UT_Character.SetCharacterAction(ATTACK_1,50,ATTACK,10,BENEFICIAL_ATTACKER);
    UT_Character.SetCharacterAction(ATTACK_2,60,LUCK,15,NEGATIVE_VICTIM);
    UT_Character.SetCharacterAction(SPELL_1,55,POWER,12,BENEFICIAL_TEAM);
    UT_Character.SetCharacterAction(SPELL_2,54,LIFE_POINTS,1,NEGATIVE_ATTACKER);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetDamage(),50);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetDamage(),60);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetDamage(),55);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetDamage(),54);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetStatBuffName(),ATTACK);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetStatBuffName(),LUCK);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetStatBuffName(),POWER);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetStatBuffName(),LIFE_POINTS);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetStatBuffValue(),15);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetStatBuffValue(),12);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetStatBuffValue(),1);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetBuffBeneficial(),NEGATIVE_VICTIM);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetBuffBeneficial(),BENEFICIAL_TEAM);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetBuffBeneficial(),NEGATIVE_ATTACKER);

    
    
    
  }
}

BOOST_AUTO_TEST_CASE(TestJSON_Tools){
  {
    Character UT_Character(IS);
    JSON_tools JSON;

    JSON.JSON_Configure_Character(UT_Character);

    BOOST_CHECK_EQUAL(UT_Character.GetMajor(), INFO);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStatus(), ALIVE);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(ATTACK), 140);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(DEFENSE), 80); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(LUCK), 5); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(POWER), 140); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(LIFE_POINTS), 80); 
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(MAX_LIFE_POINTS), 100);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetDamage(),80);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetDamage(),65);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetDamage(),80);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetDamage(),65);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetStatBuffName(),0);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetStatBuffName(),POWER);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetStatBuffName(),0);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetStatBuffName(),ATTACK);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetStatBuffValue(),20);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetStatBuffValue(),20);

    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_1)->GetBuffBeneficial(),0);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(ATTACK_2)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_1)->GetBuffBeneficial(),0);
    BOOST_CHECK_EQUAL(UT_Character.GetAction(SPELL_2)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

  }
}

BOOST_AUTO_TEST_CASE(TestState) 
{
  {
       
    State UUT_State(INITIALISATION, PLAYER_TURN);

    UUT_State.AddPlayerCharacter(SIA);
    UUT_State.AddPlayerCharacter(IS);
    UUT_State.AddPlayerCharacter(RT);
    UUT_State.AddPlayerCharacter(AEI);
    
    BOOST_CHECK_EQUAL(UUT_State.GetPlayerRosterSize(), 4);
  }
}

BOOST_AUTO_TEST_CASE(TestStats){
  {
    Stats Stats1;

    BOOST_CHECK_EQUAL(Stats1.Get_attack(),100);
    BOOST_CHECK_EQUAL(Stats1.Get_defense(),100);
    BOOST_CHECK_EQUAL(Stats1.Get_life_points(),100);
    BOOST_CHECK_EQUAL(Stats1.Get_power(),100);
    BOOST_CHECK_EQUAL(Stats1.Get_luck(),100);
    BOOST_CHECK_EQUAL(Stats1.Get_max_life_points(),100);

    Stats1.Set_max_life_points(120);
    Stats1.Set_attack(102);
    Stats1.Set_defense(101);
    Stats1.Set_life_points(90);
    Stats1.Set_luck(2);
    Stats1.Set_power(5);

    BOOST_CHECK_EQUAL(Stats1.Get_attack(),102);
    BOOST_CHECK_EQUAL(Stats1.Get_life_points(),90);
    BOOST_CHECK_EQUAL(Stats1.Get_max_life_points(),120);
    BOOST_CHECK_EQUAL(Stats1.Get_defense(),101);
    BOOST_CHECK_EQUAL(Stats1.Get_luck(),2);
    BOOST_CHECK_EQUAL(Stats1.Get_power(),5);

  }

  
}

/* vim: set sw=2 sts=2 et : */
