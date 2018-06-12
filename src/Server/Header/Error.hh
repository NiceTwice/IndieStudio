//
// Created by debruy_p on 03/05/16.
//

#ifndef CLIENT_ERROR_HH
#define CLIENT_ERROR_HH


#include <exception>
#include <string>

class Error: public std::exception {
protected:
    std::string _type;
    std::string _message;
public:
    Error(std::string const &, std::string const &);
    virtual ~Error() throw();

    const char *what() const throw();
    const char *where() const throw();
};


#endif //CLIENT_ERROR_HH
