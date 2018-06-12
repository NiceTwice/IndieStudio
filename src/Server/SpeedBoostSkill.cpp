//
// Created by debruy_p on 18/05/16.
//

#include "SpeedBoostSkill.hh"
#include "SpeedBoostBuff.hh"

SpeedBoostSkill::SpeedBoostSkill(Creature *parent):Skill(Skill::TYPE::SPEEDBOOSTBUFF, parent) {
    _cooldown = 10;
    _manaCost = 5;
    _range = 500;
}

SpeedBoostSkill::~SpeedBoostSkill() {

}

void SpeedBoostSkill::useOn(Creature *target) {
    if (target->isEnnemy())
        target = _parent;
    sendUseSkill(target);
    _parent->consumeMana(_manaCost);
    _currentCoolDown = _cooldown;
    target->addBuff(new SpeedBoostBuff());
}