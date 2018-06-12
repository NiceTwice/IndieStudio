//
// Created by nicetwice on 08/05/16.
//

#include "BodyAttack.h"
#include "SoundManager.hh"

IND::BodyAttack::BodyAttack(IND::Creature *parent, Ogre::SceneManager *sm, const std::string &icon) : Spell(parent, sm){
    _animList.push_back("Attack1H");
    _animList.push_back("Attack1H1");
    _animList.push_back("Attack2H");
    _animList.push_back("Attack2H1");
    _animList.push_back("Attack2HL");
    _animList.push_back("Attack2HL1");
    _type = IND::Spell::MeleeAttack;
    _cd = 1.0;
    _imageName = icon;//"SpellIcons/axeAttack";
}

IND::BodyAttack::~BodyAttack() {

}

void IND::BodyAttack::use(Creature *target) {
    Ogre::AnimationState        *state;
    std::string                 animTo;
    SoundManager &sm = SoundManager::getSingleton();

    if (target) {
        _currentCd = _cd;
      sm.playSound("sword");
      animTo = _animList[rand() % _animList.size()];
            state = _parent->getEntity()->getAnimationState(animTo.c_str());
            state->setTimePosition(0.0);
            state->setLoop(false);
            _parent->setAnimationState(state);
    }
}

void IND::BodyAttack::update(const Ogre::FrameEvent &evt) {
    Spell::updateCd(evt);
}







