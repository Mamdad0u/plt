// Generated by dia2code
#ifndef STATE__STATE__H
#define STATE__STATE__H

#include <vector>

namespace state {
  class Character;
  class RandomEvent;
}

#include "Character.h"
#include "RandomEvent.h"
#include "CombatStatus.h"

namespace state {

  /// class State - 
  class State {
    // Associations
    // Attributes
  private:
    const int MAX_CHARACTER     = 4;
    const int MAX_ARENA     = 4;
    const int MAX_COMBAT_NB     = 9;
    std::vector<Character> mCharacters;
    int mCombatState;
    RandomEvent mRandomEvent;
    int mArenaNumber;
    int mTurn;
    // Operations
  public:
    State ();
    std::vector<Character> GetCharacter ();
    void MoveNextTurn ();
    void ChangeCombatState (CombatStatus rNewState);
    void InitializeCharacter ();
    void InitializeMap ();
    void BeginFight (std::vector<Character> rListOfCharacter);
    void BeginRandomEvent ( );
    void GotoNextArena ();
    // Setters and Getters
  };

};

#endif
