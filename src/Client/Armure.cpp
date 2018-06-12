//
// Armure.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Tue May 31 18:45:41 2016 walbecq
// Last update Tue May 31 18:52:17 2016 walbecq
//

#include "Armure.h"
#include "SoundManager.hh"

IND::Armure::Armure(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
    _type = Spell::Type::ArmureBuff;
//    ps = sm->createParticleSystem(getParticleSystemNextName(), "MyParticle/Spiral");
//    ps->setEmitting(false);
//    mNode = sm->createSceneNode();
//    mNode->attachObject(ps);
    timer = 0;
    _cd = 10.0;
    _currentCd = 0.0;
    _imageName = "SpellIcons/armureBuff";
}

IND::Armure::~Armure() {

}

void IND::Armure::use(Creature *target) {
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
//        mNode->setPosition(0, 0.5, 0);
//        target->getSceneNode()->addChild(mNode);
//        for ( int i = 0; i < ps->getNumEmitters(); ++i )
//            ps->getEmitter( i )->setEnabled( true );
//        ps->setEmitting(true);
    }

}

void IND::Armure::update(const Ogre::FrameEvent &evt) {
    Spell::updateCd(evt);
    if (timer > 0) {
        if ((timer -= evt.timeSinceLastFrame) < 0){
//            mNode->getParentSceneNode()->removeChild(mNode);
/*            for ( int i = 0; i < ps->getNumEmitters(); ++i )
                ps->getEmitter( i )->setEnabled( false );
            ps->setEmitting(false);*/
        }
    }
    return;
}







