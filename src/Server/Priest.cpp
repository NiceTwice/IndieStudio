//
// Created by debruy_p on 18/05/16.
//

#include "Priest.hh"
#include "HealSkill.hh"
#include "ArmureBoostSkill.hh"

Priest::Priest(size_t id, Ogre::Vector3 const &position): ControlableCreature(id, position, Creature::TYPE::PRIEST) {
    _maxHp = 75;
    _hp = _maxHp;
    _maxMp = 150;
    _mp = _maxMp;
    _force = 5;
    _armure = 5;
    _skills.push_back(new HealSkill(this));
    _skills.push_back(new ArmureBoostSkill(this));
    sendSpawn();
}

Priest::~Priest() {

}