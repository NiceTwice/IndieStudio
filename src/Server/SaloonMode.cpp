//
// Created by debruy_p on 09/05/16.
//

#include <netinet/in.h>
#include <zconf.h>
#include <dnet.h>
#include <strings.h>
#include "SaloonMode.hh"
#include "Server.hh"

SaloonMode::SaloonMode(): ServerMode("Saloon") {

}

SaloonMode::~SaloonMode() {

}

int SaloonMode::treatOrder() {
    std::list<User*> users = Server::getSingleton().getUsers();

    auto it = users.begin();
    while (it != users.end())
    {
        if (this == Server::getSingleton().getServerModeManager()->getCurrentServerMode() && (*it)->isConnected() && (*it)->haveOrderToTreat()) {
            switch (*(*it)->getOrderToTreat().type) {
                case Order::TYPE::CHAT :
                    chat(*it, (*it)->getOrderToTreat());
                    it++;
                    break;
                case Order::TYPE::PING :
                    ping(*it, (*it)->getOrderToTreat());
                    it++;
                    break;
                case Order::TYPE::DECONNECT :
                    deconnect(*it);
                    it = users.end();
                    break;
                case Order::TYPE::READY :
                    ready(*it);
                    it++;
                    break;
                case Order::TYPE::STARTGAME :
                    std::cout << "J'ai recu un STARTGAME" << std::endl;
                    go(*it);
                    it++;
                    break;
                case Order::TYPE::CHARACTER :
                    std::cout << "Changement de personnage" << std::endl;
                    character(*it, (*it)->getOrderToTreat());
                    it++;
                    break;
                default :
                    wrong(*it);
                    it = users.end();
                    break;
            }
        }
        else
            it ++;
    }
    return 0;
}

int SaloonMode::work() {
    return  0;
}

void SaloonMode::chat(User *user, Order::t_order const &order) {
    std::string msg = user->getProfile().getName();

    msg += ": ";
    msg += (char*)order.data;
    Server::getSingleton().getChat()->writeMsg(msg);
    user->orderTreated();
}

void SaloonMode::ping(User * user, Order::t_order const &order) {
    user->updatePing(*((std::chrono::time_point<std::chrono::high_resolution_clock>*)order.data));
    user->stockOrderToSend(new Order(Order::TYPE::PING, sizeof(std::chrono::time_point<std::chrono::high_resolution_clock>), order.data));
    user->orderTreated();
}

void SaloonMode::deconnect(User *user) {
    std::string msg = user->getProfile().getName();

    msg += " disconnected.";
    Server::getSingleton().getChat()->writeMsg(msg);
    user->orderTreated();
    //user->sendOrder(Order(Order::TYPE::DECONNECT, 3, ":("));
    onUserDeconnect(user);
}

void SaloonMode::wrong(User *user) {
    user->orderTreated();
    Server::getSingleton().kickUser(user, "Wrong client...");
}

void SaloonMode::onProfilesChanged() {
    std::list<User *> userList = Server::getSingleton().getUsers();
    size_t size = userList.size() * PROFILELEN + sizeof(uint8_t) + sizeof(uint8_t);
    char buff[size];
    bzero(buff, size);
    *((uint8_t *)buff) = (uint8_t)userList.size();
    std::cout << userList.size() << std::endl;
    char *curs = buff + (2 * sizeof(uint8_t));
    for (auto it = userList.begin(); it != userList.end(); ++it) {
        for (int i = 0; i < (*it)->getProfile().getName().size() && i < PROFILELEN; ++i) {
            curs[i] = (*it)->getProfile().getName()[i];
        }
        curs += PROFILELEN;
    }
    int i = 0;
    for (auto it = userList.begin(); it != userList.end(); ++it) {
        if ((*it)->isConnected()) {
            *((uint8_t *)buff + sizeof(uint8_t)) = (uint8_t) i;
            (*it)->stockOrderToSend(new Order(Order::TYPE::PROFIL, size, (void *) buff));
        }
        i++;
    }
}

void SaloonMode::ready(User *user) {
     user->ready();
}

void SaloonMode::onUserTryToConnect() {
    struct sockaddr_in  s_in_client;
    socklen_t s_in_size = sizeof(s_in_client);;
    socket_t clientFd;
    User *currentUser;
    Order::t_order order;

    currentUser = NULL;
    if ((clientFd = accept(Server::getSingleton().getFd(), (sockaddr *)&s_in_client, &s_in_size)) != - 1) {
        for (auto i = Server::getSingleton().getUsers().begin(); i != Server::getSingleton().getUsers().end(); ++i) {
            if (!(*i)->isConnected()) {
                currentUser = *i;
                break;
            }
        }
        std::cout << "A client try to connect... : ";
        User tmp;
        tmp.connect(clientFd, "", NULL);
        std::string mdp("");
        tmp.receiveOrder();
        order = tmp.getOrderToTreat();
        tmp.orderTreated();
        if (currentUser == NULL) {
            tmp.sendOrder(Order(Order::TYPE::DECONNECT, 15, (void*)"Server full..."));
            std::cout << "Server full" << std::endl;
            close(clientFd);
            return ;
        }
        tmp.sendOrder(Order(Order::TYPE::MDP, 0, NULL));
        if (tmp.receiveOrder()) {
            std::cout << "Receive order failed" << std::endl;
            close(clientFd);
            return ;
        }
        order = tmp.getOrderToTreat();
        if (*order.type != Order::TYPE::MDP) {
            tmp.sendOrder(Order(Order::TYPE::DECONNECT, 16, (void*)"Wrong client..."));
            close(clientFd);
            std::cout << "Wrong client (getPassword)" << std::endl;
            return ;
        }
        else {
            mdp = (char*)order.data;
        }
        if (Server::getSingleton().getMdp().empty())
            mdp = "";
        if (mdp.compare(Server::getSingleton().getMdp()) != 0) {
            tmp.sendOrder(Order(Order::TYPE::DECONNECT, 18, (void*)"Wrong password..."));
            std::cout << "Wrong password" << std::endl;
            close(clientFd);
            return ;
        }
        tmp.orderTreated();
        tmp.sendOrder(Order(Order::TYPE::PROFIL, Server::getSingleton().getName().size() + 1, (void*)Server::getSingleton().getName().c_str()));
        if (tmp.receiveOrder()) {
            std::cout << "Receive order failed" << std::endl;
            close(clientFd);
            return ;
        }
        order = tmp.getOrderToTreat();
        if (*order.type != Order::TYPE::PROFIL) {
            tmp.sendOrder(Order(Order::TYPE::DECONNECT, 16, (void*)"Wrong client..."));
            std::cout << "Wrong client (getProfile)" << std::endl;
            close(clientFd);
            return ;
        }
        currentUser->connect(clientFd, inet_ntoa(s_in_client.sin_addr), order.data);
        std::cout << "Success" << std::endl;
        currentUser->sendOrder(Order(Order::TYPE::CHAT, 23, (void*)"Welcome to the server!"));
        std::string msg = currentUser->getProfile().getName();
        msg += " is connected";
        if (currentUser == *(Server::getSingleton().getUsers().begin())) {
            currentUser->stockOrderToSend(new Order(Order::TYPE::HOST, 0, NULL));
            msg += " as Saloon Master";
        }
        msg += "!";
        Server::getSingleton().getChat()->writeMsg(msg);
        tmp.connect(-1, "", NULL);
        Server::getSingleton().getServerModeManager()->getCurrentServerMode()->onProfilesChanged();
        tmp.orderTreated();

    }
    else {
        std::cout << "Accept fail...: ";
    }
    return ;
}

void SaloonMode::onUserDeconnect(User *user) {
    Server::getSingleton().removeUser(user);
}

void SaloonMode::go(User *user) {
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
        if ((*it)->isConnected()){
            (*it)->stockOrderToSend(new Order(Order::TYPE::STARTGAME, 0, NULL));
        }
    }
    user->orderTreated();
    Server::getSingleton().getServerModeManager()->goToMode("GameMode");
}

void SaloonMode::character(User *user, Order::t_order const &order) {
    size_t *type = (size_t*)order.data;

    user->setCharacType(*type);
    user->orderTreated();
}