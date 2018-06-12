//
// Created by debruy_p on 03/05/16.
//

#include "Error.hh"

Error::Error(const std::string &type, const std::string &message): _type(type), _message(message) {

}

Error::~Error() throw() {

}

const char *Error::what() const throw(){
    return _message.c_str();
}

const char *Error::where() const throw(){
    return _type.c_str();
}
