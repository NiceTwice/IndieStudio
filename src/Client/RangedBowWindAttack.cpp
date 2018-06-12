//
// Created by nicetwice on 10/05/16.
//

#include "RangedBowWindAttack.h"
#include "WindArrow.h"

IND::RangedBowWindAttack::RangedBowWindAttack(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/WindArrow"));
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/WindArrow"));
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/WindArrow"));
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/WindArrow"));
    _type = IND::Spell::RangeAttack;
    _cd = 1.0;
    _imageName = "SpellIcons/BowAttack";
}

IND::RangedBowWindAttack::~RangedBowWindAttack() {
    for (auto j = arrows.begin(); j != arrows.end() ; ++j) {
        delete *j;
    }
}

void IND::RangedBowWindAttack::use(Creature *target) {
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

void IND::RangedBowWindAttack::update(const Ogre::FrameEvent &evt) {
    std::vector<Creature*>::iterator            it = arrows.begin();

    Spell::updateCd(evt);
    while (it != arrows.end()) {
        (*it)->update(evt);
        it++;
    }
}
