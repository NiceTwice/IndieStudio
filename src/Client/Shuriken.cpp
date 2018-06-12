//
// Created by zibaire on 19/05/16.
//

#include "Shuriken.h"

IND::Shuriken::Shuriken(const Ogre::Vector3 &position, Entity::EntityType type,
                                Ogre::SceneManager *sceneManager) : Creature(position, type, sceneManager, 0) {
m_particles = sceneManager->createParticleSystem(getParticleSystemNextName(), "MyParticle/Fireball");

    m_particles->setEmitting(false);
    _mWalkSpeed = 1000.0;
    mEntity = sceneManager->createEntity("Sword2HEpic.mesh");
    mNode->attachObject(mEntity);
    mNode->createChildSceneNode(Ogre::Vector3(1, 0, 0))->attachObject(m_particles);
    mNode->setScale(120, 120, 120);
    _isDead = true;
    mEntity->setVisible(false);
}

IND::Shuriken::~Shuriken() {
    delete mEntity;
    delete m_particles;
    _scnMgr->getRootSceneNode()->removeChild(mNode);
    mNode->detachAllObjects();
    delete mNode;
}

void IND::Shuriken::takeDamage(Creature &targetFrom, size_t damage) {

}

void IND::Shuriken::doDamage(Creature &targetFrom, size_t damage) {

}

void IND::Shuriken::update(const Ogre::FrameEvent &evt) {
    if (_isDead == true)
        return;
    Ogre::Real mDistance;

    _mDirection = _target->getSceneNode()->getPosition() - mNode->getPosition();
    _mDirection.y = 0;
    mDistance = _mDirection.normalise();
    Ogre::Real move = _mWalkSpeed * evt.timeSinceLastFrame;
    Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
    Ogre::Quaternion quat = src.getRotationTo(_mDirection);
    mNode->rotate(quat);
    mNode->translate(move * _mDirection);
    if (mDistance < 5)
    {
        _isDead = true;
        m_particles->setEmitting(false);
        mEntity->setVisible(false);
        _target = NULL;
    }
}

void IND::Shuriken::resetAnimation() {

}

void IND::Shuriken::dead(void) {
    _isDead = true;
}

void IND::Shuriken::setTarget(Creature *tgt) {
   if (tgt)
   {
       _isDead = false;
       _target = tgt;
       mEntity->setVisible(true);
       m_particles->setEmitting(true);
   }
}
