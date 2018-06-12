//
// Created by debruy_p on 19/05/16.
//

#include "FireballMissile.hh"

FireballMissile::FireballMissile(Creature *by):Missile(Missile::TYPE::FIREBALL, by), _dammage(30) {
    _moveSpeed = 1000;

}

FireballMissile::~FireballMissile() {

}

void FireballMissile::onTarget() {
    _target->takeDammage(_dammage);
}





