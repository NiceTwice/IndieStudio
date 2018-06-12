//
// Created by zibaire on 03/06/16.
//

#ifndef CPP_INDIE_STUDIO_ARTHAS_H
#define CPP_INDIE_STUDIO_ARTHAS_H

#include "Creature.h"

namespace IND {
    class Arthas : public Creature {
    public:
        Arthas(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~Arthas();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
    };
}

#endif //CPP_INDIE_STUDIO_ARTHAS_H
