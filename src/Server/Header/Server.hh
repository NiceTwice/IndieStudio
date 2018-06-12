//
// Created by debruy_p on 25/04/16.
//

#ifndef SERVER_SERVER_HH
#define SERVER_SERVER_HH

#include <list>
#include "User.hh"
#include "Chat.hh"
#include "Thread.hh"
#include "ServerModeManager.hh"

# define    DEFAULT_MAXUSER     5
# define    USER_TIMEOUT        5.0f
# define    PING_TIME           1.0f

typedef int socket_t;

class Server {
protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> _pinger;
    int _port;
    unsigned int _maxUser;
    std::list<User*> _Users;
    unsigned int _usersConnected;
    socket_t _fd;
    std::string _name;
    std::string _mdp;
    bool _started;
    bool _stop;
    Chat *_chat;
    ServerModeManager *_serverModeManager;
    size_t                  _maxCreatureId;

public:
    static Server& getSingleton();

private:
    Server& operator= (const Server&){}
    Server (const Server&){}

    static Server m_instance;

    Server(void);
    virtual ~Server(void);

public:
    int init(std::string const &, int, std::string const &);

    void work();

    void communication();

    std::string const &getMdp() const;
    std::string const &getName() const;
    socket_t getFd() const;
    std::list<User*> const &getUsers() const;
    Chat *getChat() const;
    ServerModeManager *getServerModeManager() const;

    bool isFull() const;
    bool isEmpty() const;

    void setMaxUsers(unsigned int);
    void rename(std::string const &);
    void removeUser(User *);
    void kickUser(User *, std::string const &);

    void stockOrderForAll(Order *) const;

    void stop();
    bool isStoped() const;

    std::chrono::time_point<std::chrono::high_resolution_clock> getTimeMillis(void) const;
    float diffTime(std::chrono::time_point<std::chrono::high_resolution_clock> const &last, std::chrono::time_point<std::chrono::high_resolution_clock> const &now);

    size_t getNextId();


        // Fonction de debug

    void printStatus() const;
    void printUsers() const;
};


#endif //SERVER_SERVER_HH