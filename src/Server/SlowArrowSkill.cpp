//
// Created by debruy_p on 19/05/16.
//

#include "SlowArrowSkill.hh"
#include "SlowArrowMissile.hh"

SlowArrowSkill::SlowArrowSkill(Creature *parent) : Skill(Skill::TYPE::SLOWARROW, parent), _arrows() {
    _cooldown = 7;
    _manaCost = 1;
    _range = 1000;
}

SlowArrowSkill::~SlowArrowSkill() {
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        delete (*it);
    }
    _arrows.clear();
}

void SlowArrowSkill::update(float timeSinceLastUpdate) {
    Skill::update(timeSinceLastUpdate);
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        if ((*it)->isUsed()) {
            (*it)->update(timeSinceLastUpdate);
        }
    }
}


void SlowArrowSkill::useOn(Creature *target) {
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
        SlowArrowMissile *arrow = new SlowArrowMissile(_parent);
        arrow->launchIn(target);
        _arrows.push_back(arrow);
    }
}





