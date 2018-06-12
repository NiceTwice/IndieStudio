//
// Created by debruy_p on 25/04/16.
//

#ifndef SERVER_USER_HH
#define SERVER_USER_HH

#include <string>
#include <list>
#include <chrono>
#include "Order.hh"
#include "Profile.hh"

typedef int t_socket;

#define ORDER_BUFFLEN   16384

class User {

protected:
    bool _connected;
    std::string _ipAdress;
    Profile _profile;
    t_socket _socket;
    std::chrono::time_point<std::chrono::high_resolution_clock> _lastLive;
    std::list<Order*> _ordersToSend;
    long long _ping;
    bool _ready;
    char _orderBuff[ORDER_BUFFLEN];
    Order::t_order _currentOrder;
    size_t _characType;
public:
    User();
    virtual ~User();

    bool isConnected() const;
    std::string const &getIp() const;
    Profile const &getProfile() const;
    t_socket getSocket() const;
    std::chrono::time_point<std::chrono::high_resolution_clock> const &getLastLive() const;

    void gameDeconnect();
    void gameReconnect();
    void connect(t_socket, std::string const &ip, void *buff);
    void setIp(std::string const &);
    void setProfile(void *);
    void live();
    void updatePing(std::chrono::time_point<std::chrono::high_resolution_clock> const &);

    int sendOrder(Order const &);
    int receiveOrder();

    Order::t_order const &getOrderToTreat();
    void orderTreated();
    bool haveOrderToTreat() const;

    void stockOrderToSend(Order*);
    int sendAllOrdersToSend();

    void ready();

    size_t getUserNbr() const;

    size_t getCharacType() const;
    void    setCharacType(size_t);
};

#endif //SERVER_USER_HH