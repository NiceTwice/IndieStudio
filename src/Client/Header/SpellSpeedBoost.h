//
// Created by nicetwice on 11/05/16.
//

#ifndef OGREGAMEPLAY_SPELLSPEEDBOOST_H
#define OGREGAMEPLAY_SPELLSPEEDBOOST_H

#include "Spell.h"

namespace IND {
    class SpellSpeedBoost : public Spell{
        public:
            SpellSpeedBoost(Creature *parent, Ogre::SceneManager *sm);
            virtual ~SpellSpeedBoost();
            virtual void use(Creature *target);
            virtual void update(const Ogre::FrameEvent& evt);
        };
}

#endif //OGREGAMEPLAY_SPELLSPEEDBOOST_H
