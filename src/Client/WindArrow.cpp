//
// Created by nicetwice on 10/05/16.
//

#include "WindArrow.h"

std::string             getParticleSystemNextName(void);

IND::WindArrow::WindArrow(const Ogre::Vector3 &position, IND::Entity::EntityType type,
                          Ogre::SceneManager *sceneManager, const std::string &particle) : Creature(position, type, sceneManager, 0){
    mParticles = sceneManager->createParticleSystem(getParticleSystemNextName(), particle);

    mParticles->setEmitting(false);
    _mWalkSpeed = 1000.0;
    mEntity = sceneManager->createEntity("ArrowNormal.mesh");
    mNode->attachObject(mEntity);
    mNode->createChildSceneNode(Ogre::Vector3(1, 0, 0))->attachObject(mParticles);
    mNode->setScale(75, 75, 75);
    _isDead = true;
    mEntity->setVisible(false);
}

IND::WindArrow::~WindArrow() {
    delete mEntity;
    delete mParticles;
    mNode->detachAllObjects();
    _scnMgr->getRootSceneNode()->removeChild(mNode);
    delete mNode;
}

void IND::WindArrow::takeDamage(Creature &targetFrom, size_t damage) {

}

void IND::WindArrow::doDamage(Creature &targetFrom, size_t damage) {
}

void IND::WindArrow::update(const Ogre::FrameEvent &evt) {
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
        mEntity->setVisible(false);
        _target = NULL;
    }
}

void IND::WindArrow::resetAnimation(void) {

}

void IND::WindArrow::dead(void) {
    _isDead = true;
}

void IND::WindArrow::setTarget(Creature *tgt) {
    if (tgt) {
        _isDead = false;
        _target = tgt;
        mEntity->setVisible(true);
        mParticles->setEmitting(true);
    }
}
