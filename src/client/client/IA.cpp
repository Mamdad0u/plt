#include <client/IA.h>  // Included from library shared_static
#include "IA.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

namespace client {
    client::IA::IA(){
        srand (time(NULL));
    }


    void client::IA::SetStatusCommand(CommandID NewCommand){
        mInputCommand = NewCommand;
        NotifyNewPlayerCommand();
    }

    CommandID client::IA::GetStatusCommand () const{
        return this->mInputCommand;
    }

    void client::IA::GenerarateRandomCommand(){
        CommandID lCommandIDTab[] = {ATTACK_1, ATTACK_2, SPELL_1, SPELL_2}; 
        int lRandomInt = 0;
        static CommandID lRandomCommand;

        lRandomInt = rand() % 4;
        lRandomCommand = lCommandIDTab[lRandomInt];
        SetStatusCommand(lRandomCommand);
    }
}