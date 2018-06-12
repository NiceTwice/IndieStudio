//
// Created by debruy_p on 11/05/16.
//

#ifndef SERVER_GAMEMODE_HH
#define SERVER_GAMEMODE_HH

#include "ServerMode.hpp"
#include "Creature.hh"
#include "ControlableCreature.hh"
#include "QuadTree.hh"
#include "Wall.hh"
#include "EditFileLexer.hh"
#include "EditFileParser.hh"


class GameMode : public ServerMode {
protected:
    std::vector<Creature*>  _players;
    std::list<Creature*>    _creatures;
    std::chrono::time_point<std::chrono::high_resolution_clock>                   _lastTime;
    QuadTree *_mapTree;
    EditFileParser *_parser;

public:
    GameMode();
    virtual ~GameMode();

    int treatOrder();
    int work();

    void onProfilesChanged();
    void onUserTryToConnect();
    void onUserDeconnect(User *);
    void onSelected();
    void onDeselected();

private:
    void chat(User *, Order::t_order const &);
    void ping(User *, Order::t_order const &);
    void deconnect(User *);
    void moveTo(User *);
    void useSkill(User *);

    struct moveTo{
        float x;
        float y;
        float z;
    };
    struct skillInfo{
        Skill::TYPE type;
        size_t target;
    };
    Creature *getCreature(size_t id) const;

    void sendErrorMsg(std::string const &msg, User *user) const;
};

#endif //SERVER_GAMEMODE_HH