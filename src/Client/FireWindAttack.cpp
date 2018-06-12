//
// FireWindAttack.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Tue May 31 17:53:49 2016 walbecq
// Last update Tue May 31 18:11:37 2016 walbecq
//

#include "FireWindAttack.h"
#include "WindArrow.h"

IND::FireWindAttack::FireWindAttack(IND::Creature *parent, Ogre::SceneManager *sm) : Spell(parent, sm){
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/FirePoint"));
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/FirePoint"));
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/FirePoint"));
  arrows.push_back(new WindArrow(Ogre::Vector3::ZERO, IND::Entity::Ally, mSceneManager, "MyParticle/FirePoint"));
    _type = IND::Spell::FireWindAttack;
    _cd = 5.0;
    _imageName = "SpellIcons/FuriousAwakening";
}

IND::FireWindAttack::~FireWindAttack() {
    for (auto j = arrows.begin(); j != arrows.end() ; ++j) {
        delete *j;
    }
}

void IND::FireWindAttack::use(Creature *target) {
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

void IND::FireWindAttack::update(const Ogre::FrameEvent &evt) {
    std::vector<Creature*>::iterator            it = arrows.begin();

    Spell::updateCd(evt);
    while (it != arrows.end()) {
        (*it)->update(evt);
        it++;
    }
}
