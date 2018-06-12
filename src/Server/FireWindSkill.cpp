//
// Created by debruy_p on 01/06/16.
//

#include "FireWindSkill.hh"
#include "FireWindMissile.hh"

FireWindSkill::FireWindSkill(Creature *parent): Skill(Skill::TYPE::FIREWIND, parent), _arrows() {
    _cooldown = 5;
    _manaCost = 5;
    _range = 1000;
}

FireWindSkill::~FireWindSkill() {
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        delete (*it);
    }
    _arrows.clear();
}

void FireWindSkill::useOn(Creature *target) {
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
        FireWindMissile *arrow = new FireWindMissile(_parent);
        arrow->launchIn(target);
        _arrows.push_back(arrow);
    }
}

void FireWindSkill::update(float timeSinceLastUpdate) {
    Skill::update(timeSinceLastUpdate);
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        if ((*it)->isUsed()) {
            (*it)->update(timeSinceLastUpdate);
        }
    }
}







