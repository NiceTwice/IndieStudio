//
// Created by debruy_p on 09/05/16.
//

#ifndef SERVER_SERVERMODE_HPP
#define SERVER_SERVERMODE_HPP

#include <string>
#include "User.hh"

class ServerMode {
protected:
    std::string _name;
public:
    ServerMode(std::string const &name): _name(name) {}
    virtual ~ServerMode() {}
    std::string const &getName() const {return _name;}

    virtual int treatOrder() {};
    virtual int work() {};

    virtual void onSelected() {};
    virtual void onDeselected() {};

    virtual void onProfilesChanged() {};
    virtual void onUserTryToConnect() {};
    virtual void onUserDeconnect(User *) {};
};

#endif //SERVER_SERVERMODE_HPP
