//
// Created by debruy_p on 26/04/16.
//

#include <fcntl.h>
#include <algorithm>
#include <ctime>
#include "Chat.hh"
#include "Server.hh"

Chat::Chat(): _log() {

    std::string fileName = Server::getSingleton().getName();
    fileName += ".log";
    _log.open(fileName ,std::ios::app);
    if (_log.is_open()) {
        _logEnabled = true;
        _log << "#########################" << std::endl;
        std::time_t date = std::time(NULL);
        std::string dateStr = std::ctime(&date);
        dateStr.erase(std::remove(dateStr.begin(), dateStr.end(), '\n'), dateStr.end());
        _log << "[" << dateStr << "] ";
        _log << Server::getSingleton().getName() << std::endl;
    }
    else {
        _logEnabled = false;
        std::cerr << "Warning: Log file is not enabled..." << std::endl;
    }
}

Chat::~Chat() {
    if (_logEnabled) {
        _log << "#########################" << std::endl << std::endl;
        _log.close();
    }
}

void Chat::writeMsg(const std::string &msg)  {
    if (_logEnabled) {
        std::time_t date = std::time(NULL);
        std::string dateStr = std::ctime(&date);
        dateStr.erase(std::remove(dateStr.begin(), dateStr.end(), '\n'), dateStr.end());
        _log << "[" << dateStr << "] ";
        _log << msg << std::endl;
    }
    for (auto i = Server::getSingleton().getUsers().begin(); i != Server::getSingleton().getUsers().end(); ++i) {
        if ((*i)->isConnected()) {
            (*i)->stockOrderToSend(new Order(Order::TYPE::CHAT, msg.size() + 1, (void*)msg.c_str()));
        }
    }
    std::cout << msg << std::endl;
}