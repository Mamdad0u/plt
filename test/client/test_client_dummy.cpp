#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include "client.h"
#include "ai.h"
#include "render.h"

using namespace ::client;
using namespace ::state;
using namespace ::ai;
using namespace ::render;

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


BOOST_AUTO_TEST_CASE(TestRandomAI){
  {
  Engine NewEngine;
  RenderLayer lRender(&NewEngine);
  RandomAI IA1;
  RandomAI IA2;
  State* Game_State;
  CombatStatus GameStatus = INITIALISATION;
  int turn = 0;


  IA1.AddEngineObserver(&NewEngine);
  IA2.AddEngineObserver(&NewEngine);
  lRender.NotifyEndRendering();
  IA1.GenerarateRandomCommand();
  Game_State = NewEngine.GameLoop();
  

  
  
 
 
 
  }
}

BOOST_AUTO_TEST_SUITE_END()