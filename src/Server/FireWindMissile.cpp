//
// Created by debruy_p on 01/06/16.
//

#include "FireWindMissile.hh"
#include "InFireBuff.hh"

FireWindMissile::FireWindMissile(Creature *by):Missile(Missile::TYPE::FIREWIND, by), _dammage(15) {
    _moveSpeed = 1000;
}

FireWindMissile::~FireWindMissile() {

}

void FireWindMissile::onTarget() {
    _target->takeDammage(_dammage);
    _target->addBuff(new InFireBuff(_target));
}





