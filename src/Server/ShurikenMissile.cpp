//
// Created by debruy_p on 19/05/16.
//

#include "ShurikenMissile.hh"

ShurikenMissile::ShurikenMissile(Creature *by):Missile(Missile::TYPE::SHURIKEN, by), _dammage(10) {
    _moveSpeed = 800;
}

ShurikenMissile::~ShurikenMissile() {

}

void ShurikenMissile::onTarget() {
    _target->takeDammage(_dammage);
}




