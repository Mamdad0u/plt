<<<<<<< HEAD
#include <state/Element.h>  // Included from library shared_static
#include "Element.h"
namespace state {


state::Element::Element(){
    this->nName = DEFAULT_NAME;
    
}


state::Element::Element (std::string rName, int rX, int rY) {
    this->nName = rName;
    this->setMX(rX);
    this->setMY(rY);
}

std::string state::Element::GetName() {
    return this->nName;
}

const std::string& state::Element::getNName() const {
    
}

void state::Element::setNName(const std::string& nName) {
    
}


=======
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


>>>>>>> Engine
}