//
// Created by debruy_p on 19/05/16.
//

#include "FireballSkill.hh"
#include "FireballMissile.hh"

FireballSkill::FireballSkill(Creature *parent): Skill(Skill::TYPE::FIREBALL, parent), _arrows() {
    _cooldown = 5;
    _manaCost = 5;
    _range = 1000;
}

FireballSkill::~FireballSkill() {
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        delete (*it);
    }
    _arrows.clear();
}

void FireballSkill::useOn(Creature *target) {
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
        FireballMissile *arrow = new FireballMissile(_parent);
        arrow->launchIn(target);
        _arrows.push_back(arrow);
    }
}

void FireballSkill::update(float timeSinceLastUpdate) {
    Skill::update(timeSinceLastUpdate);
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        if ((*it)->isUsed()) {
            (*it)->update(timeSinceLastUpdate);
        }
    }
}