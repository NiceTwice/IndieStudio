//
// Created by zibaire on 19/05/16.
//

#ifndef CPP_INDIE_STUDIO_SHURIKEN_H
#define CPP_INDIE_STUDIO_SHURIKEN_H

#include "Creature.h"

namespace IND {
    class Shuriken : public Creature {
        Ogre::ParticleSystem *m_particles;
    public:
        Shuriken(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager);
        virtual ~Shuriken();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
        virtual void dead(void);
        virtual void setTarget(Creature *);
    };
}

#endif //CPP_INDIE_STUDIO_SHURIKEN_H
