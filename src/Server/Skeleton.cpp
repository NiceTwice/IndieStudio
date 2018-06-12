//
// Created by debruy_p on 13/05/16.
//

#include "Skeleton.hh"
#include "BodyAttackSkill.hh"
#include "BowAttackSkill.hh"
#include "SpeedBoostSkill.hh"
#include "FireballSkill.hh"
#include "HealSkill.hh"

Skeleton::Skeleton(size_t id, Ogre::Vector3 const &position): ControlableCreature(id, position, Creature::TYPE::SKELETON) {
    _skills.push_back(new BodyAttackSkill(this));
    _skills.push_back(new BowAttackSkill(this));
    _skills.push_back(new SpeedBoostSkill(this));
    _skills.push_back(new FireballSkill(this));
    _skills.push_back(new HealSkill(this));
    sendSpawn();
}

Skeleton::~Skeleton() {

}