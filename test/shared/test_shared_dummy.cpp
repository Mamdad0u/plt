
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

BOOST_AUTO_TEST_CASE(TestCharacter) 
{
  {
       
/*     //Character UT_Character(ELEC, DEAD, "ESE");

    UT_Character.SetCharacterStats(ATTACK, 15);
    
    BOOST_CHECK_EQUAL(UT_Character.GetMajor(), ELEC);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStatus(), DEAD);
    BOOST_CHECK_EQUAL(UT_Character.GetCharacterStats(ATTACK), 15); */
    
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


    BOOST_CHECK_EQUAL(ActionList.GetAttack(0)->GetDamage(),0);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(0)->GetStatBuffValue(),0);
    BOOST_CHECK_EQUAL(ActionList.GetAttack(0)->GetStatBuffName(),LIFE_POINTS);
    

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
/* vim: set sw=2 sts=2 et : */
