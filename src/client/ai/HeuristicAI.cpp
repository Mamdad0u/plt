#include <ai/HeuristicAI.h>  // Included from library shared_static
#include "HeuristicAI.h"
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace client;

namespace ai {

    CommandID ai::HeuristicAI::GenerateHeuristicCommand(){
        std::list<EngineObserver*>::iterator lIterator;

        lIterator = this->mEngineObserverList.begin();

        std::cout << "pouet :"<<(*lIterator)->mCurrentState.GetAlivePlayer() << std::endl;
    }


    void ai::HeuristicAI::SetStatusCommand(CommandID rNewCommand){
        mInputCommand = rNewCommand;
        NotifyNewAICommand();
    }

    CommandID ai::HeuristicAI::GetStatusCommand(){
        return this->mInputCommand;
    }

}