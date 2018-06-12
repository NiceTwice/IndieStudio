//
// Heal.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Sun May 22 16:54:35 2016 walbecq
// Last update Thu May 26 13:59:05 2016 walbecq
//

#include "Heal.h"
#include "SampleMissile.h"
#include "SoundManager.hh"

IND::Heal::Heal(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
    _type = Spell::Type::Heal;
    ps = sm->createParticleSystem(getParticleSystemNextName(), "MyParticle/Heal");
    ps->setEmitting(false);
    mNode = sm->createSceneNode();
    mNode->attachObject(ps);
    timer = 0;
    _cd = 10.0;
    _currentCd = 0.0;
    _imageName = "SpellIcons/heal";
}

IND::Heal::~Heal() {

}

void IND::Heal::use(Creature *target) {
    Ogre::AnimationState        *state;
    SoundManager &sm = SoundManager::getSingleton();

    if (target) {
        Spell::use(target);
        sm.playSound("heal");
      state = _parent->getEntity()->getAnimationState("SpellCastOmni");
      state->setTimePosition(0.0);
      state->setLoop(false);
        _parent->setAnimationState(state);
        timer = 2.0;
        mNode->setPosition(0, 0.5, 0);
        target->getSceneNode()->addChild(mNode);
        for ( int i = 0; i < ps->getNumEmitters(); ++i )
            ps->getEmitter( i )->setEnabled( true );
        ps->setEmitting(true);
    }

}

void IND::Heal::update(const Ogre::FrameEvent &evt) {
    Spell::updateCd(evt);
    if (timer > 0) {
        if ((timer -= evt.timeSinceLastFrame) < 0){
            mNode->getParentSceneNode()->removeChild(mNode);
            for ( int i = 0; i < ps->getNumEmitters(); ++i )
                ps->getEmitter( i )->setEnabled( false );
            ps->setEmitting(false);
        }
    }
    return;
}







