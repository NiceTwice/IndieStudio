//
// Created by debruy_p on 14/05/16.
//

#include "BodyAttackSkill.hh"
#include "Server.hh"

BodyAttackSkill::BodyAttackSkill(Creature *parent):Skill(Skill::TYPE::MELEE_ATTACK, parent){
    _cooldown = 1;
    _manaCost = 0;
}

BodyAttackSkill::~BodyAttackSkill() {

}

void BodyAttackSkill::useOn(Creature *target) {
    if (target != _parent) {
        sendUseSkill(target);
        _currentCoolDown = _cooldown;
        target->takeDammage(_parent->getForce());
    }
}