#include <client/IA.h>  // Included from library shared_static
#include "IA.h"

namespace client {
    void client::IA::SetStatusCommand(CommandID NewCommand){
        mInputCommand = NewCommand;
        NotifyNewPlayerCommand();
    }

    CommandID client::IA::GetStatusCommand () const{
        return this->mInputCommand;
    }
}