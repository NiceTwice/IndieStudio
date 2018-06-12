//
// Created by debruy_p on 06/05/16.
//

#include "Profile.hh"

Profile::Profile(std::string const &name):_name(name) {

}

Profile::~Profile() {

}

void Profile::setName(std::string const &name) {
    _name = name;
}

std::string const &Profile::getName() const {
    return _name;
}







