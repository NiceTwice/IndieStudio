//
// Created by nicetwice on 10/05/16.
//

#include "ShurikenAttack.h"
#include "Shuriken.h"

IND::ShurikenAttack::ShurikenAttack(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
  arrows.push_back(new IND::Shuriken(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager));
  arrows.push_back(new IND::Shuriken(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager));
  arrows.push_back(new IND::Shuriken(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager));
  arrows.push_back(new IND::Shuriken(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager));
    _type = IND::Spell::Shuriken;
    _cd = 1.0;
    _imageName = "SpellIcons/shurikenAttack";
}

IND::ShurikenAttack::~ShurikenAttack() {
    for (auto j = arrows.begin(); j != arrows.end() ; ++j) {
        delete *j;
    }
}

void IND::ShurikenAttack::use(Creature *target) {
    Ogre::AnimationState        *state;
    std::vector<Creature*>::iterator            it = arrows.begin();
    if (target) {
        _currentCd = _cd;
            state = _parent->getEntity()->getAnimationState("AttackBow");
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

void IND::ShurikenAttack::update(const Ogre::FrameEvent &evt) {
    std::vector<Creature*>::iterator            it = arrows.begin();

    Spell::updateCd(evt);
    while (it != arrows.end()) {
        (*it)->update(evt);
        it++;
    }
}
