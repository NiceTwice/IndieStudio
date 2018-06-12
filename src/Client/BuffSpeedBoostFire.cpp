//
// Created by nicetwice on 10/05/16.
//

#include "BuffSpeedBoostFire.h"

IND::BuffSpeedBoostFire::BuffSpeedBoostFire() : Buff(){
    _duration = 5.0;
}

IND::BuffSpeedBoostFire::~BuffSpeedBoostFire() {
}

void IND::BuffSpeedBoostFire::update(const Ogre::FrameEvent &evt) {
    if (_isEnded)
        return;
    _duration -= evt.timeSinceLastEvent;
    if (_duration <= 0){
        _partSystem->detachFromParent();
        _parent->setWalkSpeed(_parent->getWalkSpeed() - addedValue);
        _parent->getSceneManager()->destroyParticleSystem(_partSystem);
        _isEnded = true;
    }
}

void IND::BuffSpeedBoostFire::setTarget(Creature *target) {
    _parent = target;
    _partSystem = target->getSceneManager()->createParticleSystem(getParticleSystemNextName(), "MyParticle/WindArrow");
    target->getSceneNode()->attachObject(_partSystem);
    addedValue = target->getBasicWalkSpeed() * 0.5f;
    target->setWalkSpeed(target->getWalkSpeed() + addedValue);
}