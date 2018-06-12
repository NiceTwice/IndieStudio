//
// Created by nicetwice on 08/05/16.
//

#ifndef OGREGAMEPLAY_SKELETONARCHER_H
#define OGREGAMEPLAY_SKELETONARCHER_H

#include "Creature.h"

namespace IND {
    class SkeletonArcher : public Creature {
    public:
        SkeletonArcher(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~SkeletonArcher();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);

    };
}

#endif //OGREGAMEPLAY_SKELETONARCHER_H
