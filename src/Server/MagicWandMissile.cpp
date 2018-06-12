//
// Created by debruy_p on 19/05/16.
//

#include "MagicWandMissile.hh"

MagicWandMissile::MagicWandMissile(Creature *by):Missile(Missile::TYPE::MAGICWAND, by), _dammage(7) {
    _moveSpeed = 600;

}

MagicWandMissile::~MagicWandMissile() {

}

void MagicWandMissile::onTarget() {
    _target->takeDammage(_dammage);
}