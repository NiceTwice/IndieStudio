//
// Created by nicetwice on 10/05/16.
//

#ifndef OGREGAMEPLAY_SHURIKENATTACK_H
#define OGREGAMEPLAY_SHURIKENATTACK_H

#include "Creature.h"

namespace IND {
        class ShurikenAttack : public Spell {
            std::vector<Creature*>                  arrows;
        public:
            ShurikenAttack(Creature *parent, Ogre::SceneManager *sm);
            virtual ~ShurikenAttack();
            virtual void use(Creature *target);
            virtual void update(const Ogre::FrameEvent& evt);
        };
}

#endif //OGREGAMEPLAY_SHURIKENATTACK_H
