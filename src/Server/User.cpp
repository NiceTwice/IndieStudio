//
// Created by debruy_p on 25/04/16.
//

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <strings.h>
#include "User.hh"
#include "Server.hh"

User::User():_connected(false), _ipAdress("none"), _profile(), _socket(-1), _lastLive(Server::getSingleton().getTimeMillis()), _ordersToSend(), _ping(0), _ready(true) {

    _currentOrder.type = (Order::TYPE*)_orderBuff;
    _currentOrder.size = (size_t *)(_orderBuff + sizeof(Order::TYPE));
    _currentOrder.data = (void *)(_orderBuff + sizeof(Order::TYPE) + sizeof(size_t));
    bzero(_orderBuff, ORDER_BUFFLEN);
    _characType = 1;
}

User::~User() {
    if (_socket != -1)
    close(_socket);
    Order *tmp;
    while (!_ordersToSend.empty()) {
        tmp = _ordersToSend.front();
        delete tmp;
        _ordersToSend.pop_front();
    }
}

bool User::isConnected() const {
    return _connected;
}

std::string const &User::getIp() const {
    return _ipAdress;
}

Profile const &User::getProfile() const {
    return _profile;
}

t_socket User::getSocket() const {
    return _socket;
}

std::chrono::time_point<std::chrono::high_resolution_clock> const &User::getLastLive() const {
    return _lastLive;
}

void User::connect(t_socket socket, std::string const &ip, void *buff) {
    _socket = socket;
    _ipAdress = ip;
    _profile.loadBuffer(buff);
    _lastLive = Server::getSingleton().getTimeMillis();
    _connected = true;
    _ready = false;
}

void User::setIp(const std::string &ip) {
    _ipAdress = ip;
}

void User::setProfile(void *buff) {
    _profile.loadBuffer(buff);
}


void User::live() {
    _lastLive = Server::getSingleton().getTimeMillis();
}

void User::updatePing(std::chrono::time_point<std::chrono::high_resolution_clock> const & t) {
    _ping = std::chrono::duration_cast<std::chrono::microseconds>(Server::getSingleton().getTimeMillis() - t).count();
}

int User::sendOrder(const Order &order) {
    std::cout << "send :" << order.getType() << std::endl;
    if (write(_socket, order.getData(), order.getSize()) <= 0) {
        return 1;
    }
    return 0;
}

int User::receiveOrder() {
    if (*_currentOrder.type == Order::TYPE::NOTHING) {
        bzero(_orderBuff, ORDER_BUFFLEN);
        recv(_socket, &_orderBuff, ORDER_BUFFLEN, 0);
    }
    else {
        int i = 0;
        char *curs = (char*)_currentOrder.type;
        std::cout << curs - _orderBuff << std::endl;

        while (curs - _orderBuff < ORDER_BUFFLEN){
            _orderBuff[i] = *curs;
            curs++;
            i++;
        }
        bzero(_orderBuff + i, ORDER_BUFFLEN -i);
        recv(_socket, _orderBuff + i, (ORDER_BUFFLEN - i), 0);

    }
    _currentOrder.type = (Order::TYPE*)_orderBuff;
    _currentOrder.size = (size_t *)(_orderBuff + sizeof(Order::TYPE));
    _currentOrder.data = (void *)(_orderBuff + sizeof(Order::TYPE) + sizeof(size_t));

    return 0;
}

Order::t_order const &User::getOrderToTreat() {
    return _currentOrder;
    //return *(_ordersReceived.begin());
}

void User::orderTreated() {
  _currentOrder.data = (void *)((char *)_currentOrder.data + *_currentOrder.size + sizeof(Order::TYPE) + sizeof (size_t));
  _currentOrder.size = (size_t *)((char *)_currentOrder.data - sizeof(size_t));
    _currentOrder.type = (Order::TYPE*)((char*)_currentOrder.size - sizeof(Order::TYPE));
    //_ordersReceived.pop_front();
}

bool User::haveOrderToTreat() const {
    if (*_currentOrder.type == Order::TYPE::NOTHING
        ||(char*)_currentOrder.type > _orderBuff + ORDER_BUFFLEN
        || (char*)_currentOrder.size > _orderBuff + ORDER_BUFFLEN
        || (char*)_currentOrder.data > _orderBuff + ORDER_BUFFLEN
        || (char*)_currentOrder.data + *_currentOrder.size > _orderBuff + ORDER_BUFFLEN)
        return false;
    return *_currentOrder.type != Order::TYPE::NOTHING;
    //return !_ordersReceived.empty();
}

void User::stockOrderToSend(Order *order) {
    _ordersToSend.push_back(order);
}

int User::sendAllOrdersToSend() {
    Order *tmp;
    while (!_ordersToSend.empty()) {
        if ((tmp = _ordersToSend.front())) {
            if (sendOrder(*tmp)) {
                _ordersToSend.pop_front();
                return 1;
            }
        }
        _ordersToSend.pop_front();
        delete tmp;
    }
    return 0;
}

void User::ready() {
    _ready = !_ready;
}

void User::gameDeconnect() {
    _connected = false;
}

void User::gameReconnect() {
    _connected = true;
}

size_t User::getUserNbr() const {
    size_t i = 0;
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end(); ++it) {
        if (this == (*it))
            return i;
        i++;
    }
}

size_t User::getCharacType() const {
    return _characType;
}

void User::setCharacType(size_t type) {
    _characType = type;
}



