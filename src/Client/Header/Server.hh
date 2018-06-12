//
// Created by debruy_p on 08/05/16.
//

#ifndef TESTCEGUI_SERVER_HH
#define TESTCEGUI_SERVER_HH

#include <string>
#include <list>
#include <chrono>
#include "Order.hh"

# define    SERVER_TIMEOUT    5.0f
# define    PING_TIME       1.0f
# define    ORDER_BUFFLEN   16384

typedef int t_socket;

class Server {
protected:
    std::string _name;
    std::string _ip;
    uint16_t _port;
    t_socket _socket;
    std::list<Order> _ordersReceived;
    std::list<Order*> _ordersToSend;
    std::chrono::time_point<std::chrono::high_resolution_clock>   _lastLive;
    std::chrono::time_point<std::chrono::high_resolution_clock>  _pinger;
    char _orderBuff[ORDER_BUFFLEN];
    Order::t_order _currentOrder;
public:
    Server(std::string const &ip, uint16_t port, std::string const &mdp);
    virtual ~Server();

    void communication();
    int deconnect();

    std::string const &getName() const;

    void stockOrderToSend(Order *);

    bool haveOrderToTreat() const;
    Order::t_order const &getOrderToTreat();
    void orderTreated();

private:
    int sendAllOrdersToSend();
    void stockOrder(Order const &);
    int sendOrder(Order const &);
    int receiveOrder();
};

#endif //TESTCEGUI_SERVER_HH