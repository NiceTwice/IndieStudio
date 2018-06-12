//
// Created by debruy_p on 25/04/16.
//

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <cstring>
#include <evdns.h>
#include <chrono>
#include "Server.hh"
#include "SaloonMode.hh"
#include "GameMode.hh"

void    ctrl_c() {
    Server::getSingleton().stop();
 }

std::chrono::time_point<std::chrono::high_resolution_clock> Server::getTimeMillis(void) const{
    return std::chrono::high_resolution_clock::now();
}

Server Server::m_instance=Server();

Server::Server():_port(0),
                 _maxUser(DEFAULT_MAXUSER),
                 _Users(),
                 _usersConnected(0),
                 _name("Server"),
                 _fd(0),
                 _mdp(""),
                 _started(false),
                 _stop(false),
                 _chat(NULL),
                 _serverModeManager(NULL),
                 _maxCreatureId(0)
{

}

Server::~Server() {
    Order order(Order::TYPE::DECONNECT, 17, (void*)"Server closed...");
    for (auto i = _Users.begin(); i != _Users.end() ; ++i) {
        if ((*i)->isConnected()) {
            std::cout << "J'envois 8==D" << std::endl;
            (*i)->sendOrder(order);
        }
    }
    for (auto it = _Users.begin(); it != _Users.end(); ++it) {
        delete *it;
    }
    std::cout << "Close server socket: " << _fd <<  std::endl;
    if (close(_fd) == 0)
        std::cerr << std::strerror(errno) << std::endl;
    _Users.clear();
    delete _chat;
    delete _serverModeManager;
}

Server &Server::getSingleton() {
    return m_instance;
}

int Server::init(std::string const &name, int port, std::string const &mdp) {
    _name = name;
    _port = port;
    _mdp = mdp;
    std::cout << "Starting server...: ";
    bool sock_reuse = true;
    signal(SIGINT, (__sighandler_t) ctrl_c);
    for (unsigned int i = 0; i < DEFAULT_MAXUSER; ++i) {
        _Users.push_back(new User());
    }
    struct protoent       *pe;
    struct sockaddr_in    s_in;

    if (!(pe = getprotobyname("TCP"))) {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    if ((_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < -1) {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &sock_reuse, sizeof(int));
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(_port);
    s_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(_fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    if (listen(_fd, 42) == -1)
    {
        std::cout << std::strerror(errno) << std::endl;
        return 1;
    }
    _pinger = getTimeMillis();
    std::cout << "Success" << std::endl;
    _chat = new Chat();
    _serverModeManager = new ServerModeManager();
    _serverModeManager->addServerMode(new SaloonMode());
    _serverModeManager->addServerMode(new GameMode());
    _serverModeManager->goToMode("Saloon");
    std::cout << "###########" << std::endl;
    return 0;
}

std::list<User *> const &Server::getUsers() const {
    return _Users;
}

ServerModeManager *Server::getServerModeManager() const {
    return _serverModeManager;
}

bool Server::isFull() const {
    for (auto i = _Users.begin(); i != _Users.end() ; ++i) {
        if (!(*i)->isConnected())
            return false;
    }
    return true;
}

bool Server::isEmpty() const {
    for (auto i = _Users.begin(); i != _Users.end() ; ++i) {
        if ((*i)->isConnected())
            return false;
    }
    return true;
}

std::string const &Server::getName() const {
    return _name;
}

std::string const &Server::getMdp() const {
    return _mdp;
}

socket_t Server::getFd() const {
    return _fd;
}

Chat *Server::getChat() const {
    return _chat;
}

void Server::setMaxUsers(unsigned int maxUsers) {
    if (_maxUser < maxUsers) {
        for (unsigned int i = _maxUser; i < maxUsers; ++i) {
            _Users.push_back(new User());
        }
    }
    else if (_maxUser > maxUsers) {
        std::list<User*>::iterator tmp;
        for (int i = maxUsers; i < _maxUser; ++i) {
            tmp = _Users.end();
            tmp --;
            //kick user: Your place has been closed...
            delete(*tmp);
            _Users.remove(*tmp);
        }
    }
    _maxUser = maxUsers;
}

void Server::rename(const std::string &name) {
    _name = name;
}

void Server::removeUser(User *user) {
    for (auto i = _Users.begin(); i != _Users.end() ; ++i) {
        if ((*i) == user) {
            if (i == _Users.begin())
                _stop = true;
            _Users.remove(*i);
            delete user;
            _Users.push_back(new User());
            if (!_stop && _serverModeManager->getCurrentServerMode())
                _serverModeManager->getCurrentServerMode()->onProfilesChanged();
            return ;
        }
    }
}

void Server::kickUser(User *user, std::string const &reason) {
    user->sendOrder(Order(Order::TYPE::DECONNECT, reason.size() + 1, (void*)reason.c_str()));
    removeUser(user);
}

void Server::communication() {

    fd_set readfds;
    fd_set writefds;
    t_socket maxSocket = _fd;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(_fd, &readfds);
    for (auto i = _Users.begin(); i != _Users.end() ; ++i) {
        if ((*i)->isConnected()) {
            FD_SET((*i)->getSocket(), &readfds);
            FD_SET((*i)->getSocket(), &writefds);
            if ((*i)->getSocket() > maxSocket)
                maxSocket = (*i)->getSocket();
        }
    }
    struct timeval tv = {0, 1};
    if (select(maxSocket + 1, &readfds, &writefds, NULL, &tv) != -1) {
        if (FD_ISSET(_fd, &readfds)) {
            if (_serverModeManager->getCurrentServerMode()){
                _serverModeManager->getCurrentServerMode()->onUserTryToConnect();
            }
        }
        for (auto i = _Users.begin(); i != _Users.end(); ++i) {
            if ((*i)->isConnected()) {
                if (FD_ISSET((*i)->getSocket(), &writefds)) {
                    if ((*i)->sendAllOrdersToSend()) {
                        std::cerr << "Error: Server:: Send order failed!!!!!" << std::endl;
                    }
                }
                if (FD_ISSET((*i)->getSocket(), &readfds)) {
                    try {
                        if ((*i)->receiveOrder()) {
                            std::cerr << "Error: Receive order failed!!!!!" << std::endl;
                            std::string msg = (*i)->getProfile().getName();

                            msg += " as crashed.";
                            getChat()->writeMsg(msg);
                            if (_serverModeManager->getCurrentServerMode()){
                                _serverModeManager->getCurrentServerMode()->onUserDeconnect((*i));
                                return ;
                            }
                        }
                        if ((*i)->haveOrderToTreat())
                            (*i)->live();

                    }
                    catch (std::bad_alloc e) {
                        ;
                    }
                }
            }
        }
    }
    else {
        if (!_stop)
            std::cerr << "Error: Select fail!!!!!" << std::endl;
        else
            std::cout << "Closing server..." << std::endl;
    }

    //
    /// Check for time out
    //
    for (auto i = _Users.begin(); i != _Users.end(); ++i) {
        if ((*i)->isConnected()) {
            if (diffTime(getTimeMillis(), (*i)->getLastLive()) >= USER_TIMEOUT) {
                std::string msg = (*i)->getProfile().getName();
                msg += ": Connection timed out...";
                _chat->writeMsg(msg);
                removeUser(*i);
                break;
            }
        }
    }
    usleep(1);
}

//
// Fonctions de debug
// en dessous :)
//

void Server::printUsers() const {
    int pos = 0;
    for (auto i = _Users.begin(); i != _Users.end() ; ++i) {
        std::cout << "== Player " << pos << " ==" << std::endl;
        std::cout << "Connected: " << (*i)->isConnected() << std::endl;
        std::cout << "Ip Address: " << (*i)->getIp() << std::endl;
        std::cout << "Name:" << (*i)->getProfile().getName() << std::endl;
        pos++;
    }
}

void Server::printStatus() const {
    std::cout << "############" << std::endl;
    std::cout << "## Server ##" << std::endl;
    std::cout << "############" << std::endl << std::endl;
    std::cout << "NAME: " << _name << std::endl;
    std::cout << "STARTED: " << _started << std::endl << std::endl;

    printUsers();
    std::cout << std::endl;
}

void Server::stop() {
    _stop = true;
}

bool Server::isStoped() const {
    return _stop;
}

void Server::work() {

    while (!_stop) {
        communication();
        if (_serverModeManager->getCurrentServerMode()) {
            _serverModeManager->getCurrentServerMode()->work();
            _serverModeManager->getCurrentServerMode()->treatOrder();
        }
    }
}

float Server::diffTime(std::chrono::time_point<std::chrono::high_resolution_clock> const &now,
                       std::chrono::time_point<std::chrono::high_resolution_clock> const &last) {
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
    return (float)microseconds / 1000000.0f;
}

size_t Server::getNextId() {
    _maxCreatureId += 1;
    return _maxCreatureId;
}
