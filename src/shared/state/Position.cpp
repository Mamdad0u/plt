#include <state/Position.h>  // Included from library shared_static
#include "Position.h"
namespace state {

state::Position::Position(){
    this->mX = 0;
    this->mY = 0;
}

state::Position::Position(int x, int y) {
    this->mX = x;
    this->mY = y;
}

int state::Position::getMX() const {
    return mX;
}

int state::Position::getMY() const {
    return mY;
}


void state::Position::setMX(int x) {
    this->mX = x;
}



void state::Position::setMY(int y) {

    this->mY = y;
}
}
