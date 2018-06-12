//
// Created by debruy_p on 14/05/16.
//

#include "Missile.hh"

Missile::Missile(Missile::TYPE type, Creature *by):Entity(Ogre::Vector3::ZERO), _type(type), _origin(by), _target(NULL), _used(false) {

}

Missile::~Missile() {

}

Missile::TYPE Missile::getType() const {
    return _type;
}

Creature *Missile::getTarget() const {
    return _target;
}

Creature *Missile::getOrigin() const {
    return _origin;
}

void Missile::launchIn(Creature *target) {
    _position = _origin->getPosition();
    _target = target;
    _used = true;
}

bool Missile::isUsed() const {
    return _used;
}

void Missile::update(float timeSinceLastUpdate) {
    if (_target == NULL || _target->isDead()) {
        _used = false;
        _target = NULL;
    }
    else {
        _position += _moveSpeed * timeSinceLastUpdate * (_target->getPosition() - _position).normalisedCopy();
        float distanceTo = (_target->getPosition() - _position).normalise();
        if (distanceTo < 5) {
            onTarget();
            _used = false;
            _target = NULL;
        }
    }
}