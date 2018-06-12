//
// Created by nicetwice on 09/05/16.
//

#include "SkeletonMage.h"
#include "MagicWandAttack.h"
#include "Heal.h"
#include "SpellFireBall.h"

IND::SkeletonMage::SkeletonMage(const Ogre::Vector3 &position, IND::Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id) : Creature(position, type, sceneManager, id) {
    mEntity = sceneManager->createEntity("skeletonmale_[2]_Stand_1824.mesh");
    _hp = 0;
    _mp = 0;
    setMaxHp(75);
    setMaxMp(150);
    _mWalkSpeed = 250.0;
    _basicWalkSpeed = _mWalkSpeed;
    mNode->attachObject(mEntity);
    mNode->scale(70, 70, 70);
    currentAnimation = mEntity->getAnimationState("Stand2");
    currentAnimation->setLoop(true);
    currentAnimation->setEnabled(true);
    Ogre::ParticleSystem *mParticles = sceneManager->createParticleSystem(getParticleSystemNextName(), "MyParticle/Aureola");
    mNode->createChildSceneNode(Ogre::Vector3(0, 0.05, 0))->attachObject(mParticles);
    mParticles->setEmitting(true);
    mParticles->setKeepParticlesInLocalSpace(true);

    Ogre::ParticleSystem   *tmp = sceneManager->createParticleSystem(getParticleSystemNextName(), "MyParticle/FirePoint");

    Ogre::Entity            *arm = sceneManager->createEntity("StaffPve.mesh");

    tmp->setBoundsAutoUpdated(false);
    mEntity->attachObjectToBone("30", tmp, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.0, (float) (-0.15), 0.05));
    Ogre::Quaternion  quaternion(sqrt(0.5), 0, 0, sqrt(0.5));
    Ogre::Quaternion  rX(Ogre::Degree(-90), Ogre::Vector3::UNIT_Z);

    quaternion = quaternion * rX;
    mEntity->attachObjectToBone("43", arm, quaternion, Ogre::Vector3(-0.0, 0, 0));
    tmp = sceneManager->createParticleSystem(getParticleSystemNextName(), "MyParticle/FirePoint");
    tmp->setBoundsAutoUpdated(false);
    mEntity->attachObjectToBone("32", tmp, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.0, -0.15, -0.05));
    _spells.push_back(new MagicWandAttack(this, sceneManager));
    _spells.push_back(new SpellFireBall(this, sceneManager));
    _spells.push_back(new Heal(this, sceneManager));
}

IND::SkeletonMage::~SkeletonMage() {
    delete mEntity;
    mNode->detachAllObjects();
    _scnMgr->getRootSceneNode()->removeChild(mNode);
    delete mNode;

    for (auto j = _spells.begin(); j != _spells.end() ; ++j) {
        delete *j;
    }
}

void IND::SkeletonMage::takeDamage(Creature &targetFrom, size_t damage) {

}

void IND::SkeletonMage::doDamage(Creature &targetFrom, size_t damage) {

}

void IND::SkeletonMage::update(const Ogre::FrameEvent &evt) {
    if (_isDead){
        if (!currentAnimation->hasEnded())
            currentAnimation->addTime(evt.timeSinceLastFrame);
        Creature::update(evt);
        _deathTimer -= evt.timeSinceLastEvent;
        return;
    }
    _mDirection.y = 0;
    Ogre::Real move = _mWalkSpeed * evt.timeSinceLastFrame;
    if (!_isMooving && (_mDirection.x != 0.0 || _mDirection.z != 0.0)) {
        currentAnimation->setEnabled(false);
        currentAnimation = mEntity->getAnimationState("Run");
        currentAnimation->setLoop(true);
        currentAnimation->setEnabled(true);
        _isMooving = true;
    }
    if (_isMooving){
        if (_mDirection.x == 0.0 && _mDirection.z == 0){
            currentAnimation->setEnabled(false);
            currentAnimation = mEntity->getAnimationState("Stand2");
            currentAnimation->setLoop(true);
            currentAnimation->setEnabled(true);
            _isMooving = false;
        }
        else {
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

void IND::SkeletonMage::resetAnimation(void) {
    if (currentAnimation->hasEnded()) {
        if (_isMooving) {
            currentAnimation->setEnabled(false);
            currentAnimation = mEntity->getAnimationState("Run");
            currentAnimation->setLoop(true);
            currentAnimation->setEnabled(true);
        }
        else {
            currentAnimation->setEnabled(false);
            currentAnimation = mEntity->getAnimationState("Stand2");
            currentAnimation->setLoop(true);
            currentAnimation->setEnabled(true);
        }
    }
}
