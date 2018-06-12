//
// Created by zibaire on 26/05/16.
//

#ifndef CPP_INDIE_STUDIO_AIMOB_H
#define CPP_INDIE_STUDIO_AIMOB_H

#include "Creature.h"

namespace IND {
    class AImob : public Creature {
    public:
        AImob(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~AImob();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
    };
}

#endif //CPP_INDIE_STUDIO_AIMOB_H
