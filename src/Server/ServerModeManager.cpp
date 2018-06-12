//
// Created by debruy_p on 09/05/16.
//

#include "ServerModeManager.hh"

ServerModeManager::ServerModeManager():_serverModes(), _currentServerMode(NULL) {

}

ServerModeManager::~ServerModeManager() {
    if (_currentServerMode)
        _currentServerMode->onDeselected();
    for (auto it = _serverModes.begin(); it != _serverModes.end() ; ++it) {
        delete *(it);
    }
    _serverModes.clear();
}

void ServerModeManager::addServerMode(ServerMode *serverMode) {
    _serverModes.push_back(serverMode);
}

ServerMode *ServerModeManager::getCurrentServerMode() const {
    return _currentServerMode;
}

void ServerModeManager::goToMode(std::string const &name) {
    goToMode(getServerMode(name));
}

ServerMode *ServerModeManager::getServerMode(std::string const &name) {
    for (auto it = _serverModes.begin(); it != _serverModes.end(); ++it) {
        if ((*it)->getName().compare(name) == 0)
            return (*it);
    }
    return NULL;
}

void ServerModeManager::goToMode(ServerMode *serverMode) {
    if (serverMode) {
        if (_currentServerMode) {
            _currentServerMode->onDeselected();
        }
        serverMode->onSelected();
        _currentServerMode = serverMode;
    }
}