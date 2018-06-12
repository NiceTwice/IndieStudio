//
// Created by zibaire on 26/05/16.
//

#include <OGRE/OgreVector3.h>
#include "Golem.h"
#include "RangedBowWindAttack.h"
#include "SpellSpeedBoost.h"

IND::AImob::AImob(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id) : Creature(position, type, sceneManager, id) {
 mEntity = sceneManager->createEntity("abysalfire.mesh");
    _hp = 0;
    _mp = 0;
    setMaxHp(5);
    setMaxMp(5);
    _mWalkSpeed = 250.0;
    _basicWalkSpeed = _mWalkSpeed;
    mNode->attachObject(mEntity);
    mNode->scale(50, 50, 50);
    currentAnimation = mEntity->getAnimationState("Stand");
    currentAnimation->setLoop(true);
    currentAnimation->setEnabled(true);
    _spells.push_back(new IND::RangedBowWindAttack(this, sceneManager));
    _spells.push_back(new IND::SpellSpeedBoost(this, sceneManager));
}

IND::AImob::~AImob() {
    delete mEntity;
    mNode->detachAllObjects();
    _scnMgr->getRootSceneNode()->removeChild(mNode);
    delete mNode;

    for (auto j = _spells.begin(); j != _spells.end() ; ++j) {
        delete *j;
    }
}

void IND::AImob::takeDamage(Creature &targetFrom, size_t damage) {

}

void IND::AImob::doDamage(Creature &targetFrom, size_t damage) {

}

void IND::AImob::update(const Ogre::FrameEvent &evt) {
    if (_isDead)
    {
        if (!currentAnimation->hasEnded())
            currentAnimation->addTime(evt.timeSinceLastFrame);
        Creature::update(evt);
        _deathTimer -= evt.timeSinceLastEvent;
        return;
    }
    _mDirection.y = 0;
    Ogre::Real move = _mWalkSpeed * evt.timeSinceLastFrame;
    if (!_isMooving && (_mDirection.x != 0.0 || _mDirection.z != 0.0))
    {
        currentAnimation->setEnabled(false);
        currentAnimation = mEntity->getAnimationState("Run");
        currentAnimation->setLoop(true);
        currentAnimation->setEnabled(true);
        _isMooving = false;
    }
    if (!_isMooving)
    {
        if(_mDirection.x == 0.0 && _mDirection.z == 0) {
            currentAnimation->setEnabled(false);
            currentAnimation = mEntity->getAnimationState("Stand");
            currentAnimation->setLoop(true);
            currentAnimation->setEnabled(true);
            _isMooving = false;
        }
        else
        {
            Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
            Ogre::Quaternion quat = src.getRotationTo(_mDirection);
            mNode->rotate(quat);
            mNode->translate(move * _mDirection * correctionSpeed);
        }
    }
    resetAnimation();
    Creature::update(evt);
    currentAnimation->addTime(evt.timeSinceLastFrame);
}

void IND::AImob::resetAnimation() {
    if (currentAnimation->hasEnded())
    {
        if (_isMooving)
        {
            currentAnimation->setEnabled(false);
            currentAnimation = mEntity->getAnimationState("Run");
            currentAnimation->setLoop(true);
            currentAnimation->setEnabled(true);
        }
        else
        {
            currentAnimation->setEnabled(false);
            currentAnimation = mEntity->getAnimationState("Stand");
            currentAnimation->setLoop(true);
            currentAnimation->setEnabled(true);
        }
    }
}
