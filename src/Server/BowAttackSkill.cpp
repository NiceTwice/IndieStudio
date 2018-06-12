//
// Created by debruy_p on 14/05/16.
//

#include "BowAttackSkill.hh"
#include "ArrowMissile.hh"
#include "Server.hh"

BowAttackSkill::BowAttackSkill(Creature *parent): Skill(Skill::TYPE::BOW_ATTACK, parent), _arrows() {
    _cooldown = 1;
    _manaCost = 1;
    _range = 1000;
}

BowAttackSkill::~BowAttackSkill() {
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        delete (*it);
    }
    _arrows.clear();
}

void BowAttackSkill::useOn(Creature *target) {
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
        ArrowMissile *arrow = new ArrowMissile(_parent);
        arrow->launchIn(target);
        _arrows.push_back(arrow);
    }
}

void BowAttackSkill::update(float timeSinceLastUpdate) {
    Skill::update(timeSinceLastUpdate);
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        if ((*it)->isUsed()) {
            (*it)->update(timeSinceLastUpdate);
        }
    }
}