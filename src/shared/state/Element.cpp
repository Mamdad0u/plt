#include <state/Element.h>  // Included from library shared_static
#include "Element.h"
namespace state {


state::Element::Element(){
    this->mName = DEFAULT_NAME;
    
}


state::Element::Element (std::string rName, int rX, int rY) {
    this->mName = rName;
    this->setMX(rX);
    this->setMY(rY);
}

std::string state::Element::GetName() {
    return this->mName;
}

const std::string& state::Element::getMName() const {
    
}

void state::Element::setMName(const std::string& nName) {
    
}


}