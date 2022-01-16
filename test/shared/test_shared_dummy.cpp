
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
