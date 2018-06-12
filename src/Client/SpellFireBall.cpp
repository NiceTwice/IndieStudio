//
// Created by nicetwice on 11/05/16.
//

#include "SpellFireBall.h"
#include "SampleMissile.h"
#include "SoundManager.hh"

IND::SpellFireBall::SpellFireBall(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
    _damage = 355;
    arrows.push_back(new SampleMissile(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/FireBallParticle"));
    arrows.push_back(new SampleMissile(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/FireBallParticle"));
    _type = Spell::Type::FireBall;
    _cd = 5.0;
    _imageName = "SpellIcons/FireBall";
}

IND::SpellFireBall::~SpellFireBall() {

}

void IND::SpellFireBall::use(Creature *target) {
  Ogre::AnimationState        *state;
  // Ogre::Vector3               mDirection;
  // Ogre::Real                  mDistance;
  SoundManager &sm = SoundManager::getSingleton();
  std::vector<Creature*>::iterator            it = arrows.begin();
  if (target) {
      Spell::use(target);
    sm.playSound("FireBall");
    // mDirection = _parent->getSceneNode()->getPosition() - target->getSceneNode()->getPosition();
    // mDirection.y = 0;
    // mDistance = mDirection.normalise();
    state = _parent->getEntity()->getAnimationState("AttackThrown");
    state->setTimePosition(0.0);
    state->setLoop(false);
    _parent->setAnimationState(state);
    Ogre::Vector3 vec = _parent->getSceneNode()->getPosition();
    vec.y = 50;
    while (it != arrows.end()){
      if ((*it)->isDead()){
	(*it)->getSceneNode()->setPosition(vec);
	(*it)->setTarget(target);
	break;
      }
      it++;
    }
  }
}

void IND::SpellFireBall::update(const Ogre::FrameEvent &evt) {
    std::vector<Creature*>::iterator            it = arrows.begin();

    Spell::updateCd(evt);
    while (it != arrows.end()) {
        (*it)->update(evt);
        it++;
    }
}







