//
// Created by debruy_p on 18/05/16.
//

#include <SpeedBoostSkill.hh>
#include "Assassin.hh"
#include "BodyAttackSkill.hh"
#include "ShurikenAttackSkill.hh"

Assassin::Assassin(size_t id, Ogre::Vector3 const &position): ControlableCreature(id, position, Creature::TYPE::ASSASSIN) {
    _maxHp = 100;
    _hp = _maxHp;
    _maxMp = 75;
    _mp = _maxMp;
    _force = 15;
    _armure = 5;
    _skills.push_back(new BodyAttackSkill(this));
    _skills.push_back(new ShurikenAttackSkill(this));
    _skills.push_back(new SpeedBoostSkill(this));
    sendSpawn();
}

Assassin::~Assassin() {

}