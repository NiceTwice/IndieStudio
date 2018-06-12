//
// MagicWandAttack.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Fri Jun  3 17:49:29 2016 walbecq
// Last update Fri Jun  3 18:03:12 2016 walbecq
//

#include "MagicWandAttack.h"
#include "SampleMissile.h"
#include "SoundManager.hh"

IND::MagicWandAttack::MagicWandAttack(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
    _damage = 7;
    arrows.push_back(new SampleMissile(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/WindArrow"));
    arrows.push_back(new SampleMissile(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/WindArrow"));
    _type = Spell::Type::MagicWand;
    _cd = 1.0;
    _imageName = "SpellIcons/MagicWand";
}

IND::MagicWandAttack::~MagicWandAttack() {

}

void IND::MagicWandAttack::use(Creature *target) {
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

void IND::MagicWandAttack::update(const Ogre::FrameEvent &evt) {
    std::vector<Creature*>::iterator            it = arrows.begin();

    Spell::updateCd(evt);
    while (it != arrows.end()) {
        (*it)->update(evt);
        it++;
    }
}







