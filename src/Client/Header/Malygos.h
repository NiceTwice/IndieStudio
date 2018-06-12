//
// Created by zibaire on 03/06/16.
//

#ifndef CPP_INDIE_STUDIO_MALYGOS_H
#define CPP_INDIE_STUDIO_MALYGOS_H

#include "Creature.h"

namespace IND {
    class Malygos : public Creature {
    public:
        Malygos(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~Malygos();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
    };
}

#endif //CPP_INDIE_STUDIO_MALYGOS_H
