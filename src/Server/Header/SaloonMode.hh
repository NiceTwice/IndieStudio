//
// Created by debruy_p on 09/05/16.
//

#ifndef SERVER_SALOONMODE_HH
#define SERVER_SALOONMODE_HH


#include "ServerMode.hpp"
#include "User.hh"

class SaloonMode : public ServerMode{
protected:

public:
    SaloonMode();
    virtual ~SaloonMode();

    int treatOrder();
    int work();

    void onProfilesChanged();
    void onUserTryToConnect();
    void onUserDeconnect(User *);
private:
    void chat(User *, Order::t_order const &);
    void ping(User *, Order::t_order const &);
    void ready(User *);
    void deconnect(User *);
    void wrong(User *);
    void go(User *);
    void character(User *, Order::t_order const &);
};


#endif //SERVER_SALOONMODE_HH
