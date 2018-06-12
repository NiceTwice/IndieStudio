//
// Created by debruy_p on 14/05/16.
//

#include "Skill.hh"
#include "Server.hh"

Skill::Skill(Skill::TYPE type, Creature *parent): _type(type), _cooldown(2), _currentCoolDown(0), _manaCost(2), _parent(parent), _range(150) {

}

Skill::~Skill() {

}

bool Skill::isReady() const {
    return _currentCoolDown <= 0;
}

bool Skill::isOnRange(Creature *target) const {
    return (target->getPosition() - _parent->getPosition()).normalise() < _range;
}

bool Skill::haveEnouthMana() const {
    return _parent->getMana() >= _manaCost;
}

void Skill::update(float timeSinceLastUpdate) {
    if (_currentCoolDown > 0) {
        _currentCoolDown -= timeSinceLastUpdate;
    }
}

size_t Skill::getType() const {
    return _type;
}

void Skill::sendUseSkill(Creature *target) const {
    Skill::skillInfo buff;
    buff.type = _type;
    buff.by = _parent->getId();
    buff.to = target->getId();
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end(); ++it) {
        if ((*it)->isConnected()) {
            (*it)->stockOrderToSend(new Order(Order::TYPE::USE_SKILL, sizeof(Skill::skillInfo), &buff));
        }
    }
}
