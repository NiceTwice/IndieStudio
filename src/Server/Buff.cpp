//
// Created by debruy_p on 18/05/16.
//

#include "Buff.hh"

Buff::~Buff() {

}

size_t Buff::getType() const {
    return _type;
}

float Buff::getLifeMul() const {
    return _life;
}

float Buff::getManaMul() const {
    return _mana;
}

float Buff::getForceMul() const {
    return _force;
}

float Buff::getArmureMul() const {
    return _armure;
}

float Buff::getSpeedMul() const {
    return _speed;
}

bool Buff::isDead() const {
    return _time <= 0;
}

size_t Buff::getDammage() const {
    return _dammage;
}

void Buff::update(float timeSinceLastUpdate) {
    _time -= timeSinceLastUpdate;
}