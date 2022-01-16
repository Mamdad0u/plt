#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include "client.h"


using namespace ::client;
using namespace ::state;

const float STRENGTH     = 2;
const float  NEUTRAL     = 1;
const float WEAK     = 0.5;

BOOST_AUTO_TEST_SUITE( test_client_dummy1 )


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSFML)
{
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});
  }
}

BOOST_AUTO_TEST_CASE(TestCommand){
  {
/*     Engine UUT_Engine;
    state::Character UUT_Character_IS("IS", state::INFO, state::ALIVE);
    state::Character UUT_Character_SIA("SIA", state::SIGNAL, state::ALIVE);

    UUT_Character_IS.SetCharacterStats(LIFE_POINTS, 80);
    UUT_Character_IS.SetCharacterStats(ATTACK, 140);
    UUT_Character_IS.SetCharacterStats(POWER, 140);
    UUT_Character_IS.SetCharacterStats(DEFENSE, 80);
    UUT_Character_IS.SetCharacterStats(LUCK, 5);
    UUT_Character_IS.SetCharacterAction(state::ATTACK_1, 80, LUCK, 0, true);
    UUT_Character_IS.SetCharacterAction(state::ATTACK_2, 60, POWER, 20, true);
    UUT_Character_IS.SetCharacterAction(state::SPELL_1, 80, POWER, 0, true);
    UUT_Character_IS.SetCharacterAction(state::SPELL_2, 60, ATTACK, 20, true);




    UUT_Character_SIA.SetCharacterStats(LIFE_POINTS, 110);
    UUT_Character_SIA.SetCharacterStats(ATTACK, 80);
    UUT_Character_SIA.SetCharacterStats(POWER, 150);
    UUT_Character_SIA.SetCharacterStats(DEFENSE, 60);
    UUT_Character_SIA.SetCharacterStats(LUCK, 3);
    UUT_Character_SIA.SetCharacterAction(state::ATTACK_1, 60, LUCK, 3, false); 
    UUT_Character_SIA.SetCharacterAction(state::ATTACK_2, 80, LUCK, 0, true); 

    UUT_Character_SIA.SetCharacterAction(state::SPELL_1, 80, LUCK, 0, true); 
    UUT_Character_SIA.SetCharacterAction(state::SPELL_2, 60, LUCK, 3, true); 

    BOOST_CHECK_EQUAL(UUT_Engine.DEBUG_GetGameStatus(), state::IN_COMBAT);
 */



    //UUT_Engine.mCommand.ComputeAction(*(&UUT_Character_IS), *(&UUT_Character_SIA), CommandID::ATTACK_2);

    
    

/*     for(int i = 0; i<2;i++){
      //UUT_Engine.mCommand.ComputeCriticalHit(UUT_Character_IS.GetCharacterStats(LUCK));
      UUT_Engine.mCommand.ComputeAction(*(&UUT_Character_SIA), *(&UUT_Character_IS), CommandID::ATTACK_1);
      UUT_Engine.mCommand.ComputeAction(*(&UUT_Character_IS), *(&UUT_Character_SIA), CommandID::ATTACK_1);
      
    } */
     

  }




}

/* BOOST_AUTO_TEST_CASE(TestEngine){
  {
  Engine NewEngine;
  
  IA IA1;
  IA IA2;
  JSON_tools tools;
  Character test;
  CombatStatus GameStatus = INITIALISATION;
  int turn = 0;


  IA1.AddEngineObserver(&NewEngine);
  IA2.AddEngineObserver(&NewEngine);

  while(GameStatus != GAME_OVER){

    if(turn%2 == 0 && GameStatus == IN_COMBAT){
        IA1.GenerarateRandomCommand();
    }

    else if(GameStatus == IN_COMBAT){
        IA2.GenerarateRandomCommand();
    }
    turn++;
    GameStatus = NewEngine.GameLoop();
  }
  
  NewEngine.GameLoop();
 
 
  }
} */

/* ******* TEST UNITAIRE DES CLASSES DU RENDER ********** */

BOOST_AUTO_TEST_CASE(TestRenderLayer){
  {
    RenderLayer lRender;
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "ENSEAi");
    static int lArena_Number;
    lRender.LoadBackground(lArena_Number);

    lRender.LoadCharacter(1,250,250,1);
    lRender.LoadCharacter(2,200,300,1);
    lRender.LoadCharacter(5,150,350,1);
    lRender.LoadCharacter(7,100,400,1);
    lRender.LoadEnemy(1, 600,325,0);
    lRender.LoadEnemy(3,600,325,0);
    lRender.LoadEnemy(1,600,325,0);
    lRender.LoadEnemy(2,600,325,0);
    lRender.AnimateCharacters();
    lRender.GoNextCombat(window);
    lRender.GoNextArena();

    lRender.UpdateCharacterOnScreen(1,1);
    lRender.LoadUI();

    lRender.draw(window,1,IN_COMBAT);          
  }
}

BOOST_AUTO_TEST_CASE(TestRenderObserver){
  {
    Engine GameEngine;
    RenderLayer lRender(&GameEngine);

  }
}

BOOST_AUTO_TEST_CASE(NewTestSurface){
  {
    render::Surface lSurface;
    sf::RenderWindow window;


    lSurface.LoadShape("Arena1.png",0,0);
    lSurface.LoadCharacterSprite("Character1.png",0,0,0);
    lSurface.LoadBackgroundSprite("Arena2.png");
    lSurface.SetCharacterAnimation(0);
    lSurface.UpdateCharacterAnimation(1);

    lSurface.MoveBackgroundView(window,0);
    lSurface.MoveCharacterSprite();
    lSurface.ResetSpritePosition(0);
    lSurface.ResetViewPosition();

    lSurface.DrawSprite(window);


  }
}

BOOST_AUTO_TEST_CASE(TestUI){
  {
    sf::RenderWindow window;
    UI lUI;
    lUI.CreateWindow(0,0,100,50);
    lUI.AddTextWindow("Test Unitaire",0,0);
    lUI.SetTextVersion("2.0");
    lUI.DEBUG_SetTextCombatState("En train de tester");
    lUI.DEBUG_SetTextAction1("Test1");
    lUI.DEBUG_SetTextAction2("Test2");
    lUI.DEBUG_SetTextAction3("Test3");
    lUI.DEBUG_SetTextAction4("Test4");
    lUI.DEBUG_SetLifePoints();
    lUI.MoveUI();

  }
}

/*************** TEST UNITAIRE DES CLASSES DE L'ENGINE ************/

BOOST_AUTO_TEST_CASE(TestCommand){
  {
    Command lCommand;

    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(ELEC,ELEC),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(ELEC,INFO),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(ELEC,AUTO),WEAK);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(ELEC,SIGNAL),STRENGTH);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(ELEC,SCIENCES_HUMAINES),NEUTRAL);

    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(INFO,ELEC),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(INFO,INFO),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(INFO,AUTO),STRENGTH);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(INFO,SIGNAL),WEAK);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(INFO,SCIENCES_HUMAINES),NEUTRAL);

    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(AUTO,ELEC),STRENGTH);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(AUTO,INFO),WEAK);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(AUTO,AUTO),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(AUTO,SIGNAL),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(AUTO,SCIENCES_HUMAINES),NEUTRAL);

    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SIGNAL,ELEC),WEAK);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SIGNAL,INFO),STRENGTH);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SIGNAL,AUTO),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SIGNAL,SIGNAL),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SIGNAL,SCIENCES_HUMAINES),NEUTRAL);

    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SCIENCES_HUMAINES,ELEC),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SCIENCES_HUMAINES,INFO),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SCIENCES_HUMAINES,AUTO),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SCIENCES_HUMAINES,SIGNAL),NEUTRAL);
    BOOST_CHECK_EQUAL(lCommand.ComputeWeakAndStrength(SCIENCES_HUMAINES,SCIENCES_HUMAINES),STRENGTH);

    Character Character1(IS);
    Character Character2(EVE);
    JSON_tools JSON;
    JSON.JSON_Configure_Character(Character1);
    JSON.JSON_Configure_Character(Character2);

    int PVLost;
    PVLost=0;
    PVLost=lCommand.ComputeAction(Character1,Character2,engine::ATTACK_1);


    PVLost=abs(PVLost);


    int valeur_exacte=27;
    /*
    if (PVLost>50){
      
      BOOST_CHECK_EQUAL(PVLost,valeur_exacte*2);
    }
    if(PVLost<50){
      BOOST_CHECK_EQUAL(PVLost,valeur_exacte);
    }
    */

   int i;
   int count=0;
   std::cout.setstate(std::ios_base::failbit);
   for(i=0;i<=10000;i++){
     
     if(lCommand.ComputeCriticalHit(1)==2){
       count++;
     }
   }
   std::cout.clear();
  BOOST_CHECK_SMALL(count,200);
  
    
    
    
    
  }
}

BOOST_AUTO_TEST_CASE(TestPlayer){
  Player lPlayer;
  sf::RenderWindow window; 

  lPlayer.SetStatusCommand(CommandID::ATTACK_1);

  BOOST_CHECK_EQUAL(lPlayer.GetStatusCommand(),CommandID::ATTACK_1);

}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()