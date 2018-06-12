//
// BuffSlowBoost.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Thu May 26 18:55:21 2016 walbecq
// Last update Tue May 31 17:31:34 2016 walbecq
//

#include "BuffSlowBoost.h"

IND::BuffSlowBoost::BuffSlowBoost() : Buff(){
    _duration = 5.0;
}

IND::BuffSlowBoost::~BuffSlowBoost() {
}

void IND::BuffSlowBoost::update(const Ogre::FrameEvent &evt) {
    if (_isEnded)
        return;
    _duration -= evt.timeSinceLastEvent;
    if (_duration <= 0){
        _partSystem->detachFromParent();
        _parent->setWalkSpeed(_parent->getWalkSpeed() + addedValue);
        _parent->getSceneManager()->destroyParticleSystem(_partSystem);
        _isEnded = true;
    }
}

void IND::BuffSlowBoost::setTarget(Creature *target) {
    _parent = target;
    _partSystem = target->getSceneManager()->createParticleSystem(getParticleSystemNextName(), "MyParticle/SlowBuff");
    target->getSceneNode()->attachObject(_partSystem);
    addedValue = target->getBasicWalkSpeed() * 0.5f;
    target->setWalkSpeed(target->getWalkSpeed() - addedValue);
}
