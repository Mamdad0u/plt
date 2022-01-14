#include <engine/Player.h>  // Included from library shared_static
#include "Player.h"

namespace engine {
    void engine::Player::SetStatusCommand(CommandID NewCommand){
        
        mInputCommand = NewCommand;
        NotifyNewPlayerCommand();
    }

    CommandID engine::Player::GetStatusCommand () const{
        return this->mInputCommand;
    }

    void engine::Player::ClickCommand (sf::RenderWindow& rWindow, engine::WindowCursor rCursor){
        if(rCursor.ClickAction1(rWindow)){
            SetStatusCommand( ATTACK_1 );
        }
        if(rCursor.ClickAction2(rWindow)){
            SetStatusCommand( ATTACK_2 );
        }
        if(rCursor.ClickAction3(rWindow)){
            SetStatusCommand( SPELL_1 );
        }
        if(rCursor.ClickAction4(rWindow)){
            SetStatusCommand( SPELL_2 );
        }
    }
}