//
// ArmureBuff.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Tue May 31 18:23:41 2016 walbecq
// Last update Tue May 31 18:25:56 2016 walbecq
//

#include "ArmureBuff.h"

IND::ArmureBuff::ArmureBuff() : Buff(){
    _duration = 5.0;
}

IND::ArmureBuff::~ArmureBuff() {
}

void IND::ArmureBuff::update(const Ogre::FrameEvent &evt) {
    if (_isEnded)
        return;
    _duration -= evt.timeSinceLastEvent;
    if (_duration <= 0){
        _partSystem->detachFromParent();
        _parent->getSceneNode()->removeChild(node);
        _parent->getSceneManager()->destroyParticleSystem(_partSystem);
        delete node;
        _isEnded = true;
    }
}

void IND::ArmureBuff::setTarget(Creature *target) {
    _isEnded = false;
    _parent = target;
    _partSystem = target->getSceneManager()->createParticleSystem(getParticleSystemNextName(), "MyParticle/ShieldBuff");
    node = target->getSceneNode()->createChildSceneNode(Ogre::Vector3(0, 1, 0));
    node->attachObject(_partSystem);
    _partSystem->setKeepParticlesInLocalSpace(true);
}
