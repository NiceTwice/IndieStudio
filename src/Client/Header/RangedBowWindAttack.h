//
// Created by nicetwice on 10/05/16.
//

#ifndef OGREGAMEPLAY_RANGEDBOWWINDATTACK_H
#define OGREGAMEPLAY_RANGEDBOWWINDATTACK_H

#include "Creature.h"

namespace IND {
        class RangedBowWindAttack : public Spell {
            std::vector<Creature*>                  arrows;
        public:
            RangedBowWindAttack(Creature *parent, Ogre::SceneManager *sm);
            virtual ~RangedBowWindAttack();
            virtual void use(Creature *target);
            virtual void update(const Ogre::FrameEvent& evt);
        };
}

#endif //OGREGAMEPLAY_RANGEDBOWWINDATTACK_H
