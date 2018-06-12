//
// Created by debruy_p on 27/04/16.
//

#include <string.h>
#include "Profile.hh"

Profile::Profile():_name("Open") {

}

Profile::~Profile() {

}

void Profile::setName(const std::string &name) {
    _name = name;
}

std::string const &Profile::getName() const {
    return _name;
}

void *Profile::getBuffer() const {
    char *buff = new char[PROFILELEN];
    bzero(buff, PROFILELEN);
    const char *str = _name.c_str();
    int i = 0;
    while (str[i]) {
        buff[i] = str[i];
        i++;
    }
    return ((void*)buff);
}

void Profile::loadBuffer(void *buff) {
    if (buff)
        _name = (char*)buff;
}
