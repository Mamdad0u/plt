#include <client/Command.h>  // Included from library shared_static
#include "Command.h"

using namespace state;

namespace client {
    float client::Command::ComputeWeakAndStrength(state::Major rAttackerMajor, state::Major rVictimMajor){
        
        switch(rAttackerMajor){
            case ELEC:
                switch (rVictimMajor)
                {
                case ELEC:
                    return NEUTRAL;

                case INFO:
                    return NEUTRAL;

                case AUTO:
                    return WEAK;

                case SIGNAL:
                    return STRENGTH;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;

                }
                break;
            
            case INFO:
                switch (rVictimMajor)
                {
                case ELEC:
                    return NEUTRAL;

                case INFO:
                    return NEUTRAL;

                case AUTO:
                    return STRENGTH;

                case SIGNAL:
                    return WEAK;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;
                }
                break;

            case AUTO:
                switch (rVictimMajor)
                {
                case ELEC:
                    return STRENGTH;

                case INFO:
                    return WEAK;

                case AUTO:
                    return NEUTRAL;

                case SIGNAL:
                    return NEUTRAL;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;

                }
                break;

            case SIGNAL:
                switch (rVictimMajor)
                {
                case ELEC:
                    return WEAK;

                case INFO:
                    return STRENGTH;

                case AUTO:
                    return NEUTRAL;

                case SIGNAL:
                    return NEUTRAL;

                case SCIENCES_HUMAINES:
                    return NEUTRAL;
                }
                break;

            case SCIENCES_HUMAINES:
                switch (rVictimMajor)
                {
                case SCIENCES_HUMAINES:
                    return STRENGTH;
                

                default: // All other major
                    return NEUTRAL;
                }
                break;
        }
        
    }


}