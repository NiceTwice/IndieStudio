//
// Created by debruy_p on 18/05/16.
//

#include <Creature.hh>
#include "SpeedBoostBuff.hh"

SpeedBoostBuff::SpeedBoostBuff() {
    _type = SPEEDBOOST;
    _life = 1.0;
    _force = 1.0;
    _mana = 1.0;
    _armure = 1.0;
    _speed = 1.5;
    _time = 5;
}

SpeedBoostBuff::~SpeedBoostBuff() {

}

