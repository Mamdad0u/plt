
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

BOOST_AUTO_TEST_CASE(TestAction){
  {
    Action Action{};
    BOOST_CHECK_EQUAL(Action.GetDamage(),0);
    BOOST_CHECK_EQUAL(Action.GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(Action.GetStatBuffName(),LIFE_POINTS);

    Action.SetDamage(50);
    BOOST_CHECK_EQUAL(Action.GetDamage(),50);

    Action.SetStatBuffName(DEFENSE);
    BOOST_CHECK_EQUAL(Action.GetStatBuffName(),DEFENSE);

    Action.SetStatBuffValue(10);
    BOOST_CHECK_EQUAL(Action.GetStatBuffValue(),10);

    Action.SetBuffBeneficial(BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(Action.GetBuffBeneficial(),BENEFICIAL_ATTACKER);

  }
}

BOOST_AUTO_TEST_CASE(TestActionList){
  {
    ActionList ActionList{};

/*
    BOOST_CHECK_EQUAL(ActionList.GetAttack(0)->GetDamage(),0);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(0)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(0)->GetStatBuffName(),LIFE_POINTS);
    */
    

    ActionList.SetAttack(1,50,DEFENSE,10,BENEFICIAL_ATTACKER);
    
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetDamage(),50);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetStatBuffName(),DEFENSE);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

    ActionList.SetAttack(2,50,DEFENSE,10,BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetDamage(),50);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetStatBuffName(),DEFENSE);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

    ActionList.SetSpell(1,50,DEFENSE,10,BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetDamage(),50);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetStatBuffName(),DEFENSE);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(1)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

    ActionList.SetSpell(2,50,DEFENSE,10,BENEFICIAL_ATTACKER);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetDamage(),50);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetStatBuffName(),DEFENSE);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetStatBuffValue(),10);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(2)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);


  }
}

BOOST_AUTO_TEST_CASE(TestCharacter) 
{
  {
       
  Character Character1(IS);

  BOOST_CHECK_EQUAL(Character1.GetMajor(),INFO);
  
  Character1.SetCharacterStatus(ALIVE);
  Character1.SetCharacterStats(MAX_LIFE_POINTS,150);
  Character1.SetCharacterStats(LIFE_POINTS,15);
  Character1.SetCharacterStats(ATTACK,2);
  Character1.SetCharacterStats(DEFENSE,12);
  Character1.SetCharacterStats(LUCK,3);
  Character1.SetCharacterStats(POWER,4);

  Character1.SetCharacterAction(ATTACK_1,40,ATTACK,10,BENEFICIAL_ATTACKER);
  Character1.SetCharacterAction(ATTACK_2,40,ATTACK,10,BENEFICIAL_ATTACKER);
  Character1.SetCharacterAction(SPELL_1,40,POWER,10,BENEFICIAL_ATTACKER);
  Character1.SetCharacterAction(SPELL_2,40,POWER,10,BENEFICIAL_ATTACKER);
  
  BOOST_CHECK_EQUAL(Character1.GetCharacterStatus(),ALIVE);
  BOOST_CHECK_EQUAL(Character1.GetCharacterStats(MAX_LIFE_POINTS),150);
  BOOST_CHECK_EQUAL(Character1.GetCharacterStats(LIFE_POINTS),15);
  BOOST_CHECK_EQUAL(Character1.GetCharacterStats(ATTACK),2);
  BOOST_CHECK_EQUAL(Character1.GetCharacterStats(DEFENSE),12);
  BOOST_CHECK_EQUAL(Character1.GetCharacterStats(LUCK),3);
  BOOST_CHECK_EQUAL(Character1.GetCharacterStats(POWER),4);

  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_1)->GetDamage(),40);
  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_1)->GetStatBuffName(),ATTACK);
  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_1)->GetStatBuffValue(),10);
  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_1)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_2)->GetDamage(),40);
  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_2)->GetStatBuffName(),ATTACK);
  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_2)->GetStatBuffValue(),10);
  BOOST_CHECK_EQUAL(Character1.GetAction(ATTACK_2)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_1)->GetDamage(),40);
  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_1)->GetStatBuffName(),POWER);
  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_1)->GetStatBuffValue(),10);
  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_1)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_2)->GetDamage(),40);
  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_2)->GetStatBuffName(),POWER);
  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_2)->GetStatBuffValue(),10);
  BOOST_CHECK_EQUAL(Character1.GetAction(SPELL_2)->GetBuffBeneficial(),BENEFICIAL_ATTACKER);

  }
}


/* vim: set sw=2 sts=2 et : */
