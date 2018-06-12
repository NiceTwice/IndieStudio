//
// Created by debruy_p on 18/05/16.
//

#include <HealSkill.hh>
#include "Mage.hh"
#include "FireballSkill.hh"
#include "MagicWandSkill.hh"

Mage::Mage(size_t id, Ogre::Vector3 const &position): ControlableCreature(id, position, Creature::TYPE::MAGE) {
    _maxHp = 75;
    _hp = _maxHp;
    _maxMp = 150;
    _mp = _maxMp;
    _force = 5;
    _armure = 5;
    _skills.push_back(new MagicWandSkill(this));
    _skills.push_back(new FireballSkill(this));
    _skills.push_back(new HealSkill(this));
    sendSpawn();
}

Mage::~Mage() {

}