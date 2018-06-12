//
// Created by debruy_p on 19/05/16.
//

#include "ArmureBoostSkill.hh"
#include "ArmureBuff.hh"

ArmureBoostSkill::ArmureBoostSkill(Creature *parent):Skill(Skill::TYPE::ARMUREBUFF, parent) {
    _cooldown = 10;
    _manaCost = 5;
    _range = 500;
}

ArmureBoostSkill::~ArmureBoostSkill() {

}

void ArmureBoostSkill::useOn(Creature *target) {
    if (target->isEnnemy())
        target = _parent;
    sendUseSkill(target);
    _parent->consumeMana(_manaCost);
    _currentCoolDown = _cooldown;
    target->addBuff(new ArmureBuff());
}