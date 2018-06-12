//
// Created by debruy_p on 09/05/16.
//

#ifndef TESTCEGUI_SERVEREXCEPTION_HH
#define TESTCEGUI_SERVEREXCEPTION_HH

#include <string>
#include <exception>

class ServerException : public std::exception{
protected:
    std::string _what;
public:
    ServerException(std::string const &);
    virtual ~ServerException() throw();

    const char *what() const throw();
};


#endif //TESTCEGUI_SERVEREXCEPTION_HH
