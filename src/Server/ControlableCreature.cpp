//
// Created by debruy_p on 18/05/16.
//

#include "ControlableCreature.hh"
#include "Server.hh"

ControlableCreature::ControlableCreature(size_t id, Ogre::Vector3 const &position, size_t type): Creature(id, position, type), _respawnTime(0) {
}

ControlableCreature::~ControlableCreature() {

}

void ControlableCreature::reSpawn() {
    _position = Ogre::Vector3::ZERO;
    _moveTo = _position;
    _distanceTo = 0;
    _hp =_maxHp;
    _mp = _maxMp;
    _dead = false;
    resurect buff;
    buff.id = _id;
    buff.x = 0;
    buff.y = 0;
    buff.z = 0;
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
        if ((*it)->isConnected()){
            (*it)->stockOrderToSend(new Order(Order::TYPE::RESPAWN, sizeof(resurect), &buff));
        }
    }
}

void ControlableCreature::dead() {
    Creature::dead();
    _respawnTime = 10.0f;
}

void ControlableCreature::update(float timeSinceLastWork, std::pair<std::list<Creature *>, std::list<Wall *>> const &list) {
    if (_dead) {
        _respawnTime -= timeSinceLastWork;
        if (_respawnTime <= 0) {
            _respawnTime = 0;
            reSpawn();
        }
    }
    Creature::update(timeSinceLastWork, list);
}