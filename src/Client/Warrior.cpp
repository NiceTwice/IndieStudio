//
// Created by nicetwice on 08/05/16.
//

#include "Warrior.h"
#include "BodyAttack.h"
#include "RangedBowWindAttack.h"
#include "SpellSpeedBoost.h"
#include "SpellFireBall.h"
#include "Armure.h"

std::string             getParticleSystemNextName(void);

IND::Warrior::Warrior(const Ogre::Vector3 &position, IND::Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id) : Creature(position, type, sceneManager, id) {
    //mEntity = sceneManager->createEntity("skeletonmale_[2]_Stand_1824.mesh");
    mEntity = sceneManager->createEntity("orc.mesh");

    _hp = 0;
    _mp = 0;
    setMaxHp(150);
    setMaxMp(50);
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
    Ogre::Entity *ent = sceneManager->createEntity("ShieldBlackTample.mesh");

    mEntity->attachObjectToBone("43", ent, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.0, (float) (-0.15), -0.05));
    ent = sceneManager->createEntity("AxeCitadel.mesh");
    mEntity->attachObjectToBone("45", ent, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.0, -0.15, -0.05));
    _spells.push_back(new BodyAttack(this, sceneManager, "SpellIcons/axeAttack"));
    _spells.push_back(new Armure(this, sceneManager));
    _spells.push_back(new SpellSpeedBoost(this, sceneManager));
}

IND::Warrior::~Warrior() {
    delete mEntity;
    mNode->detachAllObjects();
    _scnMgr->getRootSceneNode()->removeChild(mNode);
    delete mNode;

    for (auto j = _spells.begin(); j != _spells.end() ; ++j) {
        delete *j;
    }
}

void IND::Warrior::takeDamage(Creature &targetFrom, size_t damage) {

}

void IND::Warrior::doDamage(Creature &targetFrom, size_t damage) {

}

void IND::Warrior::update(const Ogre::FrameEvent &evt) {
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

void IND::Warrior::resetAnimation(void) {
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












