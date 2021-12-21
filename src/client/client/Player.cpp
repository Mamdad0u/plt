#include <client/Player.h>  // Included from library shared_static
#include "Player.h"

namespace client {
    void client::Player::SetStatusCommand(CommandID NewCommand){
        
        mInputCommand = NewCommand;
        NotifyNewPlayerCommand();
    }

    CommandID client::Player::GetStatusCommand () const{
        return this->mInputCommand;
    }

    void client::Player::ClickCommand (sf::RenderWindow& rWindow, client::WindowCursor rCursor){
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