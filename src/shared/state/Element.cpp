#include <state/Element.h>  // Included from library shared_static
#include "Element.h"
namespace state {


state::Element::Element (std::string rName, int rX, int rY) {
    this->nName = rName;
    this->nOrigine.setMX(rX);
    this->nOrigine.setMX(rY);
}

std::string state::Element::GetName() {
    return this->nName;
}

Position state::Element::GetPosition() {
    
}

const std::string& state::Element::getNName() const {
    
}

void state::Element::setNName(const std::string& nName) {
    
}

const Position& state::Element::getNOrigine() const {
    
}

void state::Element::setNOrigine(const Position& nOrigine) {
    
}
}