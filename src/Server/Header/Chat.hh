//
// Created by debruy_p on 26/04/16.
//

#ifndef SERVER_CHAT_HH
#define SERVER_CHAT_HH

#include <iostream>
#include <fstream>

class Chat {
protected:
    bool _logEnabled;
    std::ofstream _log;
public:
    Chat();
    virtual ~Chat();

    void writeMsg(std::string const &) ;
};

#endif //SERVER_CHAT_HH