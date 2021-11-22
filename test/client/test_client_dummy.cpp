
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include "client/Engine.h"

using namespace ::client;

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

BOOST_AUTO_TEST_CASE(TestEngine){
  {
    Engine UUT_Engine;

    BOOST_CHECK_EQUAL(UUT_Engine.DEBUG_GetGameStatus(), state::IN_COMBAT);

    
  }




}



