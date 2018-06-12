//
// Created by debruy_p on 18/05/16.
//

#include "Archer.hh"
#include "BowAttackSkill.hh"
#include "SlowArrowSkill.hh"
#include "SpeedBoostSkill.hh"
#include "FireWindSkill.hh"

Archer::Archer(size_t id, Ogre::Vector3 const &position): ControlableCreature(id, position, Creature::TYPE::ARCHER) {
    _maxHp = 100;
    _hp = _maxHp;
    _maxMp = 75;
    _mp = _maxMp;
    _force = 10;
    _armure = 5;
    _skills.push_back(new BowAttackSkill(this));
    _skills.push_back(new SlowArrowSkill(this));
    _skills.push_back(new FireWindSkill(this));
    sendSpawn();
}

Archer::~Archer() {

}