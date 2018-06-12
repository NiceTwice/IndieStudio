//
// Created by nicetwice on 09/05/16.
//

#ifndef OGREGAMEPLAY_SKELETONMAGE_H
#define OGREGAMEPLAY_SKELETONMAGE_H

#include <OGRE/Ogre.h>
#include "Entity.h"
#include "Creature.h"

namespace IND {
    class SkeletonMage : public Creature{
    public:
        SkeletonMage(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~SkeletonMage();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
    };
}

#endif //OGREGAMEPLAY_SKELETONMAGE_H
