//
// Created by debruy_p on 09/05/16.
//

#include "ServerException.hh"

ServerException::ServerException(std::string const &str): _what(str) {

}

ServerException::~ServerException() throw(){

}

const char *ServerException::what() const throw() {
    return _what.c_str();
}





