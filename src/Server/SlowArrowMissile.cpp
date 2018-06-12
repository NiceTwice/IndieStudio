//
// Created by debruy_p on 19/05/16.
//

#include "SlowArrowMissile.hh"
#include "SlowBoostBuff.hh"

SlowArrowMissile::SlowArrowMissile(Creature *by):Missile(Missile::TYPE::SLOWARROW, by), _dammage(7) {
    _moveSpeed = 1000;
}

SlowArrowMissile::~SlowArrowMissile() {

}

void SlowArrowMissile::onTarget() {
    _target->takeDammage(_dammage);
    _target->addBuff(new SlowBoostBuff());
}





