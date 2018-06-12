//
// Created by nicetwice on 11/05/16.
//

#include "SampleMissile.h"

IND::SampleMissile::SampleMissile(const Ogre::Vector3 &position, Entity::EntityType type,
                                  Ogre::SceneManager *sceneManager, const std::string &particleName) : Creature(position, type, sceneManager, 0){
    mParticles = sceneManager->createParticleSystem(getParticleSystemNextName(), particleName);

    mParticles->setEmitting(false);
    _mWalkSpeed = 700.0;
    mNode->createChildSceneNode()->attachObject(mParticles);
    mNode->setScale(75, 75, 75);
    _isDead = true;
}

IND::SampleMissile::~SampleMissile() {

}

void IND::SampleMissile::takeDamage(Creature &targetFrom, size_t damage) {

}

void IND::SampleMissile::doDamage(Creature &targetFrom, size_t damage) {

}

void IND::SampleMissile::update(const Ogre::FrameEvent &evt) {
    if (_isDead)
        return;
    Ogre::Real                      mDistance;
    _mDirection = _target->getSceneNode()->getPosition() - mNode->getPosition();
    _mDirection.y = 0;
    mDistance = _mDirection.normalise();
    Ogre::Real move = _mWalkSpeed * evt.timeSinceLastFrame;
    Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
    Ogre::Quaternion quat = src.getRotationTo(_mDirection);
    mNode->rotate(quat);
    mNode->translate(move * _mDirection);
    if (mDistance < 5){
        _isDead = true;
        mParticles->setEmitting(false);
        _target = NULL;
    }
}

void IND::SampleMissile::resetAnimation(void) {

}

void IND::SampleMissile::dead(void) {
    _isDead = true;
}

void IND::SampleMissile::setTarget(Creature *tgt) {
    _isDead = false;
    _target = tgt;
    mParticles->setEmitting(true);
}
