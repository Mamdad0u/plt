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


    void ai::RandomAI::SetStatusCommand(engine::CommandID NewCommand){
        mInputCommand = NewCommand;
        NotifyNewAICommand();
    }

    engine::CommandID ai::RandomAI::GetStatusCommand () const{
        return this->mInputCommand;
    }

    void ai::RandomAI::GenerarateRandomCommand(){
        engine::CommandID lCommandIDTab[] = {engine::ATTACK_1, engine::ATTACK_2, engine::SPELL_1, engine::SPELL_2}; 
        int lRandomInt = 0;
        static engine::CommandID lRandomCommand;

        lRandomInt = rand() % 4;
        lRandomCommand = lCommandIDTab[lRandomInt];
        SetStatusCommand(lRandomCommand);


        

    }
}