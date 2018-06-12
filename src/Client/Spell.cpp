//
// Created by nicetwice on 08/05/16.
//

#include "Spell.h"

IND::Spell::Spell(IND::Creature *parent, Ogre::SceneManager *sm) {
    _parent = parent;
    mSceneManager = sm;
    _currentCd = 0;
    _cd = 2;
}

IND::Spell::~Spell() {

}

IND::Spell::Type IND::Spell::getType(void) const {
    return _type;
}

float IND::Spell::getCurrentCd(void) const {
    return _currentCd;
}

float IND::Spell::getMaxCd(void) const {
    return _cd;
}

void IND::Spell::use(Creature *target) {
    _currentCd = _cd;
}

void IND::Spell::updateCd(const Ogre::FrameEvent &evt) {
    if (_currentCd > 0 && (_currentCd -= evt.timeSinceLastFrame) < 0)
        _currentCd = 0;

}

std::string const &IND::Spell::getImageName(void) const {
    return _imageName;
}
















