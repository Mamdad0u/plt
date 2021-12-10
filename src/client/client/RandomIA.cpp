#include <client/RandomIA.h>  // Included from library shared_static
#include "RandomIA.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

namespace client {
    client::RandomIA::RandomIA(){
        srand (time(NULL));
    }


    void client::RandomIA::SetStatusCommand(CommandID NewCommand){
        mInputCommand = NewCommand;
        NotifyNewPlayerCommand();
    }

    CommandID client::RandomIA::GetStatusCommand () const{
        return this->mInputCommand;
    }

    void client::RandomIA::GenerarateRandomCommand(){
        CommandID lCommandIDTab[] = {ATTACK_1, ATTACK_2, SPELL_1, SPELL_2}; 
        int lRandomInt = 0;
        static CommandID lRandomCommand;

        lRandomInt = rand() % 4;
        lRandomCommand = lCommandIDTab[lRandomInt];
        SetStatusCommand(lRandomCommand);

        std::list<EngineObserver*>::iterator lIterator;

        lIterator = this->mEngineObserverList.begin();
       
        std::cout << "pouet :"<<(*lIterator)->mCurrentState.GetAlivePlayer() << std::endl;
        

    }
}