//
// Created by debruy_p on 11/05/16.
//

#include "GameMode.hh"
#include "Server.hh"
#include "CreatureFactory.hh"

GameMode::GameMode(): ServerMode("GameMode") {
    _lastTime = Server::getSingleton().getTimeMillis();
    _parser = new EditFileParser("maps/exemple.map");
}

GameMode::~GameMode() {

}

int GameMode::treatOrder() {
    std::list<User*> users = Server::getSingleton().getUsers();

    auto it = users.begin();
    while (it != users.end())
    {
        if ((*it)->isConnected() && (*it)->haveOrderToTreat()) {
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
                case Order::TYPE::MOVETO :
                    moveTo(*it);
                    break;
                case Order::TYPE::USE_SKILL :
                    useSkill(*it);
                    break;
                default :
                    (*it)->orderTreated();
                    break;
            }
        }
        else
            it ++;
    }
    return 0;
}

int GameMode::work() {
    std::chrono::time_point<std::chrono::high_resolution_clock> now = _lastTime;
    _lastTime = Server::getSingleton().getTimeMillis();
    float timeSinceLastWork = Server::getSingleton().diffTime(_lastTime, now);
    for (auto it = _players.begin(); it != _players.end(); ++it) {
        (*it)->update(timeSinceLastWork, _mapTree->getCollableObjects(*it));
        _mapTree->updateCreature(*it);
        (*it)->syncronize();
    }
    for (auto it = _creatures.begin(); it != _creatures.end(); ++it) {
        (*it)->ai(timeSinceLastWork, _players);
        (*it)->update(timeSinceLastWork, _mapTree->getCollableObjects(*it));
        _mapTree->updateCreature(*it);
        (*it)->syncronize();
    }

    for (auto it = _creatures.begin(); it != _creatures.end(); ++it) {
        if ((*it)->isDead()) {
            Creature *tmp = (*it);
            _mapTree->popCreature(tmp);
            _creatures.remove((*it));
            delete tmp;
            it = _creatures.begin();
        }
    }
    return 0;
}

void GameMode::onProfilesChanged() {

}

void GameMode::onUserTryToConnect() {

}

void GameMode::onUserDeconnect(User *user) {

}

void GameMode::onSelected() {

    Creature *player;
    std::vector<Creature *> creatures;
    std::vector<Wall *> walls;


    try {
        _parser->parseFile();
        EditFile::Map map = _parser->getMap();
        _mapTree = new QuadTree(map._length, map._width, map._complexity);
        int i = 0;
        for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
            if ((*it)->isConnected()) {
                player = CreatureFactory::createCreature((Creature::TYPE)(*it)->getCharacType(), Ogre::Vector3(0, 0, i * 200), Server::getSingleton().getNextId());
                player->controledBy((*it));
                player->setAlly();
                _players.push_back(player);
                _mapTree->pushCreature(player);
                i++;
            }
        }

        creatures = _parser->getCreatures();
        walls = _parser->getWalls();
        for (auto it = creatures.begin(); it != creatures.end() ; ++it) {
            _mapTree->pushCreature(*it);
            _creatures.push_back(*it);
        }
        for (auto it = walls.begin(); it != walls.end() ; ++it) {
            _mapTree->pushWall(*it);
        }
    } catch (std::ios_base::failure e) {
        throw std::invalid_argument(e.what());
    } catch (std::logic_error e) {
        throw std::invalid_argument(e.what());
    }
}

void GameMode::onDeselected() {
    for (auto it = _players.begin(); it != _players.end() ; ++it) {
        delete *it;
    }
    _players.clear();
    for (auto it = _creatures.begin(); it != _creatures.end() ; ++it) {
        delete *it;
    }
    _creatures.clear();
}

//
/// PRIVATE
//

void GameMode::chat(User *user, Order::t_order const &order) {
    std::string msg = user->getProfile().getName();

    msg += ": ";
    msg += (char*)order.data;
    Server::getSingleton().getChat()->writeMsg(msg);
    user->orderTreated();
}

void GameMode::ping(User * user, Order::t_order const &order) {
    user->updatePing(*((std::chrono::time_point<std::chrono::high_resolution_clock>*)order.data));
    user->stockOrderToSend(new Order(Order::TYPE::PING, sizeof (std::chrono::time_point<std::chrono::high_resolution_clock>), order.data));
    user->orderTreated();
}

void GameMode::deconnect(User *user) {
    std::string msg = user->getProfile().getName();

    msg += " disconnected.";
    Server::getSingleton().getChat()->writeMsg(msg);
    user->orderTreated();
    if (user == *Server::getSingleton().getUsers().begin()){
        Server::getSingleton().removeUser(user);
    }
    else {
        user->gameDeconnect();
    }
}

void GameMode::moveTo(User *user) {
    Order::t_order const &order = user->getOrderToTreat();
    if (!_players[user->getUserNbr()]->isDead()) {
        Ogre::Vector3 direction(((struct moveTo *) order.data)->x, ((struct moveTo *) order.data)->y,
                                ((struct moveTo *) order.data)->z);
        _players[user->getUserNbr()]->moveTo(direction);
        //_mapTree.updateCreature(_players[user->getUserNbr()]);
    }
    else {
        sendErrorMsg("You are dead...", user);
    }
    user->orderTreated();
}

void GameMode::useSkill(User *user) {
    Order::t_order const &order = user->getOrderToTreat();
    if (!_players[user->getUserNbr()]->isDead()) {
        _players[user->getUserNbr()]->useSkill(user, ((struct skillInfo *) order.data)->type,
                                               getCreature(((struct skillInfo *) order.data)->target));
    }
    else {
        sendErrorMsg("You are dead...", user);
    }
    user->orderTreated();
}

//
/// PRIVATE
//

Creature *GameMode::getCreature(size_t id) const {
    for (auto it = _players.begin(); it != _players.end() ; ++it) {
        if (id == (*it)->getId())
            return (*it);
    }
    for (auto it = _creatures.begin(); it != _creatures.end() ; ++it) {
        if (id == (*it)->getId())
            return (*it);
    }
    return NULL;
}

void GameMode::sendErrorMsg(const std::string &msg, User *user) const {
    user->stockOrderToSend(new Order(Order::TYPE::ERROR_MSG, msg.size() + 1, (void*)msg.c_str()));
}