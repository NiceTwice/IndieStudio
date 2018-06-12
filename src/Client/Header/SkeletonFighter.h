//
// Created by nicetwice on 09/05/16.
//

#ifndef OGREGAMEPLAY_SKELETONFIGHTER_H
#define OGREGAMEPLAY_SKELETONFIGHTER_H

#include <OGRE/OgreFrameListener.h>
#include "Creature.h"

namespace IND {
    class SkeletonFighter : public Creature{
    public:
        SkeletonFighter(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~SkeletonFighter();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
    };

}

#endif //OGREGAMEPLAY_SKELETONFIGHTER_H
