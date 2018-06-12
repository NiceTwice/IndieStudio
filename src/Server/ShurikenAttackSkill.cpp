//
// Created by debruy_p on 19/05/16.
//

#include "ShurikenAttackSkill.hh"
#include "ShurikenMissile.hh"

ShurikenAttackSkill::ShurikenAttackSkill(Creature *parent): Skill(Skill::TYPE::SHURIKEN, parent), _arrows() {
    _cooldown = 1;
    _manaCost = 1;
    _range = 1000;
}

ShurikenAttackSkill::~ShurikenAttackSkill() {
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        delete (*it);
    }
    _arrows.clear();
}

void ShurikenAttackSkill::update(float timeSinceLastUpdate) {
    Skill::update(timeSinceLastUpdate);
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        if ((*it)->isUsed()) {
            (*it)->update(timeSinceLastUpdate);
        }
    }
}


void ShurikenAttackSkill::useOn(Creature *target) {
    if (target != _parent) {
        _parent->consumeMana(_manaCost);
        sendUseSkill(target);
        _currentCoolDown = _cooldown;
        for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
            if (!(*it)->isUsed()){
                (*it)->launchIn(target);
                return ;
            }
        }
        ShurikenMissile *arrow = new ShurikenMissile(_parent);
        arrow->launchIn(target);
        _arrows.push_back(arrow);
    }
}





