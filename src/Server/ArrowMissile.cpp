//
// Created by debruy_p on 14/05/16.
//

#include "ArrowMissile.hh"

ArrowMissile::ArrowMissile(Creature *by):Missile(Missile::TYPE::ARROW, by), _dammage(15) {
    _moveSpeed = 1000;
}

ArrowMissile::~ArrowMissile() {

}

void ArrowMissile::onTarget() {
    _target->takeDammage(_dammage);
}