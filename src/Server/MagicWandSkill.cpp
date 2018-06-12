//
// Created by debruy_p on 19/05/16.
//

#include "MagicWandSkill.hh"
#include "MagicWandMissile.hh"

MagicWandSkill::MagicWandSkill(Creature *parent): Skill(Skill::TYPE::MAGICWAND, parent), _arrows() {
    _cooldown = 1;
    _manaCost = 1;
    _range = 1000;

}

MagicWandSkill::~MagicWandSkill() {
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        delete (*it);
    }
    _arrows.clear();
}

void MagicWandSkill::update(float timeSinceLastUpdate) {
    Skill::update(timeSinceLastUpdate);
    for (auto it = _arrows.begin(); it != _arrows.end() ; ++it) {
        if ((*it)->isUsed()) {
            (*it)->update(timeSinceLastUpdate);
        }
    }
}

void MagicWandSkill::useOn(Creature *target) {
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
        MagicWandMissile *arrow = new MagicWandMissile(_parent);
        arrow->launchIn(target);
        _arrows.push_back(arrow);
    }
}







