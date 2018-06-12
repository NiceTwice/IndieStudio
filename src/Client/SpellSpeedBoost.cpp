//
// Created by nicetwice on 11/05/16.
//

#include "SpellSpeedBoost.h"
#include "BuffSpeedBoostFire.h"

IND::SpellSpeedBoost::SpellSpeedBoost(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
    _type = Spell::SpeedBoost;
    _cd = 10.0;
    _imageName = "SpellIcons/BuffSpeed";
}

IND::SpellSpeedBoost::~SpellSpeedBoost() {

}

void IND::SpellSpeedBoost::use(Creature *target) {
    Spell::use(target);
}

void IND::SpellSpeedBoost::update(const Ogre::FrameEvent &evt) {
    Spell::updateCd(evt);
}







