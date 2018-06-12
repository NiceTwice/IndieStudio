//
// Created by debruy_p on 09/05/16.
//

#ifndef SERVER_SERVERMODEMANAGER_HH
#define SERVER_SERVERMODEMANAGER_HH

#include <list>
#include "ServerMode.hpp"

class ServerModeManager {
protected:
    std::list<ServerMode*> _serverModes;
    ServerMode * _currentServerMode;
public:
    ServerModeManager();
    virtual ~ServerModeManager();

    void addServerMode(ServerMode* serverMode);
    ServerMode *getCurrentServerMode() const;

    ServerMode *getServerMode(std::string const &name);

    void goToMode(std::string const &name);
    void goToMode(ServerMode *serverMode);
};


#endif //SERVER_SERVERMODEMANAGER_HH
