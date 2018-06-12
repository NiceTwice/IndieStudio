//
// Created by debruy_p on 01/06/16.
//

#include <Creature.hh>
#include "InFireBuff.hh"

InFireBuff::InFireBuff(Creature *target): _target(target) {
    _type = INFIRE;
    _life = 1.0;
    _force = 1.0;
    _mana = 1.0;
    _armure = 1.0;
    _speed = 1.0;
    _dammage = 15;
    _time = 5;
    t = 0;
}

InFireBuff::~InFireBuff() {

}

void InFireBuff::update(float timeSinceLastUpdate) {
    Buff::update(timeSinceLastUpdate);
    t += timeSinceLastUpdate;
    if (t >= 1)
    {
        _target->takeDammage(_dammage);
        t -= 1;
    }
}