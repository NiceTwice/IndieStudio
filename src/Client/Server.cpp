//
// Created by debruy_p on 08/05/16.
//

#include <dnet.h>
#include <sys/socket.h>
#include <iostream>
#include "Server.hh"
#include "TutorialApplication.h"
#include "ServerException.hh"

Server::Server(std::string const &ip, uint16_t port, std::string const &mdp):_name("Server"),_ip(ip), _port(port), _socket(-1), _ordersReceived(), _ordersToSend(), _lastLive(TutorialApplication::getSingleton().getTimeMillis()), _pinger(TutorialApplication::getSingleton().getTimeMillis()) {


//    _orderBuff = NULL;

    _currentOrder.type = (Order::TYPE*)_orderBuff;
    _currentOrder.size = (size_t *)(_orderBuff + sizeof(Order::TYPE));
    _currentOrder.data = (void *)(_orderBuff + sizeof(Order::TYPE) + sizeof(size_t));
    bzero(_orderBuff, ORDER_BUFFLEN);

    struct protoent       *pe;
    struct sockaddr_in    s_in;

    if (!(pe = getprotobyname("TCP"))) {
        throw ServerException("Impossible to connect...");

    }
    if ((_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) <= -1) {
        throw ServerException("Impossible to connect...");
    }
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(_port);
    s_in.sin_addr.s_addr = inet_addr(_ip.c_str());
    if (connect(_socket, (const sockaddr *) &s_in, sizeof(s_in)) == -1){
        throw ServerException("Impossible to connect...");
    }
    _lastLive = TutorialApplication::getSingleton().getTimeMillis();

    Order::t_order order;

    if (sendOrder(Order(Order::TYPE::HEY, 0, NULL))) {
        throw ServerException("Impossible to connect...");
    }
    if (receiveOrder())
    {
        // display on window : "Impossible to connect..."
        throw ServerException("Impossible to connect...");
    }
    order = _currentOrder;
    std::cout << (void*)_orderBuff << std::endl;

    std::cout << &(*order.type) << std::endl;
    if (*order.type == Order::TYPE::DECONNECT) {
        // display on window : (char*)order.getData
        std::cerr << order.data << std::endl;
        throw ServerException((char*)order.data);
    }
    if (*order.type != Order::TYPE::MDP) {
        throw ServerException("The server seems corrupted...");
    }
    if (sendOrder(Order(Order::TYPE::MDP, mdp.size() + 1, (void*)mdp.c_str()))) {
        throw ServerException("Impossible to connect...");
    }
    orderTreated();
    if (receiveOrder()) {
        throw ServerException("Impossible to connect...");
    }
    order = getOrderToTreat();
    if (*order.type == Order::TYPE::DECONNECT) {
        // display on window : (char*)order.getData
        throw ServerException((char*)order.data);
    }
    else if (*order.type != Order::TYPE::PROFIL) {
        throw ServerException("The server seems corrupted...");
    }
    _name = (char*)order.data;
    orderTreated();
    char buff[PROFILELEN];
    bzero(buff, PROFILELEN);
    for (int i = 0; i < PROFILELEN && i < TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile()->getName().size(); ++i) {
        buff[i] = TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile()->getName()[i];
    }
    if (sendOrder(Order(Order::TYPE::PROFIL, PROFILELEN, (void*)buff))) {
        throw ServerException("Impossible to connect...");
    }
}

int Server::sendOrder(const Order &order) {
    if (write(_socket, order.getData(), order.getSize()) <= 0)
        return 1;
    return 0;
    /*size_t type = order.getType();
    size_t size = order.getSize();
    std::cout << type << std::endl;
    if (write(_socket, &type, sizeof(Order::TYPE)) < 1)
        return 1;
    if (write(_socket, &size, sizeof(size_t)) < 1)
        return 1;
    if (order.getData()) {
        if (write(_socket, order.getData(), size) == -1)
            return 1;
    }
    return 0;*/
}

int Server::receiveOrder() {
    if (*_currentOrder.type == Order::TYPE::NOTHING) {
        bzero(_orderBuff, ORDER_BUFFLEN);
        read(_socket, _orderBuff, ORDER_BUFFLEN);
    }
    else {
        size_t i = 0;
        char *curs = (char*)_currentOrder.type;
        while (curs - _orderBuff < ORDER_BUFFLEN){
            _orderBuff[i] = *curs;
            curs++;
            i++;
        }
        bzero(curs, ORDER_BUFFLEN - i);
        recv(_socket, curs, (ORDER_BUFFLEN - i), 0);
    }
    _currentOrder.type = (Order::TYPE*)_orderBuff;
    _currentOrder.size = (size_t *)(_orderBuff + sizeof(Order::TYPE));
    _currentOrder.data = (void *)(_orderBuff + sizeof(Order::TYPE) + sizeof(size_t));
    return 0;
}

void Server::stockOrder(Order const &order) {
    _ordersReceived.push_back(order);
}

Order::t_order const &Server::getOrderToTreat() {
    return _currentOrder;

    //return *(_ordersReceived.begin());
}

void Server::orderTreated() {

    /*delete[] _orderBuff;
    _orderBuff = NULL;*/
    _currentOrder.data = (void *)((char*)(_currentOrder.data) + *_currentOrder.size + sizeof(Order::TYPE) + sizeof (size_t));
    _currentOrder.size = (size_t *)((char*)(_currentOrder.data) - sizeof(size_t));
    _currentOrder.type = (Order::TYPE*)((char*)_currentOrder.size - sizeof(Order::TYPE));


}

bool Server::haveOrderToTreat() const {
    //return (_orderBuff != NULL);

    if (*_currentOrder.type == Order::TYPE::NOTHING
        || (char*)_currentOrder.type > _orderBuff + ORDER_BUFFLEN
        || (char*)_currentOrder.size > _orderBuff + ORDER_BUFFLEN
        || (char*)_currentOrder.data > _orderBuff + ORDER_BUFFLEN
        || (char*)_currentOrder.data + *_currentOrder.size > _orderBuff + ORDER_BUFFLEN)
        return false;
    return *_currentOrder.type != Order::TYPE::NOTHING;


}

void Server::stockOrderToSend(Order *order) {
    _ordersToSend.push_back(order);
}

int Server::sendAllOrdersToSend() {
    Order *tmp;
    while (!_ordersToSend.empty()) {
        tmp = _ordersToSend.front();
        if (sendOrder(*tmp))
            return 1;
        delete tmp;
        _ordersToSend.pop_front();
    }
    return 0;
}

void Server::communication() {
    fd_set readfds;
    fd_set writefds;
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;

    //
    /// GESTION DE LA COMMUNICATION
    //

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(_socket, &readfds);
    FD_SET(_socket, &writefds);

    if (select(_socket + 1, &readfds, &writefds, NULL, NULL) != -1) {
        if (FD_ISSET(_socket, &readfds)) {
            if (receiveOrder()) {
                TutorialApplication::getSingleton().getServer()->deconnect();
                TutorialApplication::getSingleton().deconnectServer();
                TutorialApplication::getSingleton().getViewManager()->goToMenu();
                TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
                std::cerr << "Error: Receive order failed!!!!!" << std::endl;
                return ;
            }
            else {
                _lastLive = TutorialApplication::getSingleton().getTimeMillis();
                //stockOrder(currentOrder);
            }
        }
        if (FD_ISSET(_socket, &writefds)) {
            if (sendAllOrdersToSend()) {
                std::cerr << "Error: Send order failed!!!!!" << std::endl;
                TutorialApplication::getSingleton().getServer()->deconnect();
                TutorialApplication::getSingleton().deconnectServer();
                TutorialApplication::getSingleton().getViewManager()->goToMenu();
                TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
                return;
            }
        }
    }
    else {
        std::cerr << "Error: Select fail!!!!!" << std::endl;
    }

    //
    /// Ping
    //
    if (TutorialApplication::getSingleton().diffTime(TutorialApplication::getSingleton().getTimeMillis(), _pinger) >= PING_TIME) {
        currentTime = TutorialApplication::getSingleton().getTimeMillis();
        stockOrderToSend(new Order(Order::TYPE::PING, sizeof(float), (char *)&currentTime));
        _pinger = currentTime;
    }

    //
    /// Check Time out
    //
    if (TutorialApplication::getSingleton().diffTime(TutorialApplication::getSingleton().getTimeMillis(), _pinger) >= SERVER_TIMEOUT) {
        std::cerr << "Connection timed out..." << std::endl;
    }

}

std::string const &Server::getName() const {
    return _name;
}

int Server::deconnect() {
    Order order(Order::TYPE::DECONNECT, 0, NULL);
    sendOrder(order);
    return 0;
}

Server::~Server() {
    close(_socket);
    for (auto it = _ordersToSend.begin(); it != _ordersToSend.end() ; ++it) {
        delete (*it);
    }
    _ordersToSend.clear();
}