//
// Created by debruy_p on 19/05/16.
//

#include "HealSkill.hh"

HealSkill::HealSkill(Creature *parent):Skill(Skill::TYPE::HEAL, parent) {
    _cooldown = 10;
    _manaCost = 5;
    _heal = 30;
    _range = 1000;
}

HealSkill::~HealSkill() {

}

void HealSkill::useOn(Creature *target) {
    if (target->isEnnemy())
        target = _parent;
    sendUseSkill(target);
    _parent->consumeMana(_manaCost);
    _currentCoolDown = _cooldown;
    target->heal(_heal);
}





