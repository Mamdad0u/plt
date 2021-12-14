#include <ai/RandomAI.h>  // Included from library shared_static
#include "RandomAI.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

namespace ai {
    ai::RandomAI::RandomAI(){
        srand (time(NULL));
    }


    void ai::RandomAI::SetStatusCommand(client::CommandID NewCommand){
        mInputCommand = NewCommand;
        NotifyNewAICommand();
    }

    client::CommandID ai::RandomAI::GetStatusCommand () const{
        return this->mInputCommand;
    }

    void ai::RandomAI::GenerarateRandomCommand(){
        client::CommandID lCommandIDTab[] = {client::ATTACK_1, client::ATTACK_2, client::SPELL_1, client::SPELL_2}; 
        int lRandomInt = 0;
        static client::CommandID lRandomCommand;

        lRandomInt = rand() % 4;
        lRandomCommand = lCommandIDTab[lRandomInt];
        SetStatusCommand(lRandomCommand);


        

    }
}