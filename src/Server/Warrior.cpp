//
// Created by debruy_p on 18/05/16.
//

#include <SpeedBoostSkill.hh>
#include "Warrior.hh"
#include "BodyAttackSkill.hh"
#include "ArmureBoostSkill.hh"
#include "SpeedBoostSkill.hh"

Warrior::Warrior(size_t id, Ogre::Vector3 const &position): ControlableCreature(id, position, Creature::TYPE::WARRIOR) {
    _maxHp = 150;
    _hp = _maxHp;
    _maxMp = 50;
    _mp = _maxMp;
    _force = 20;
    _armure = 10;
    _skills.push_back(new BodyAttackSkill(this));
    _skills.push_back(new ArmureBoostSkill(this));
    _skills.push_back(new SpeedBoostSkill(this));
    sendSpawn();
}

Warrior::~Warrior() {

}
