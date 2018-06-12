//
// Created by nicetwice on 10/05/16.
//

#ifndef OGREGAMEPLAY_WINDARROW_H
#define OGREGAMEPLAY_WINDARROW_H

#include "Creature.h"

namespace IND {
    class WindArrow : public Creature {
        Ogre::ParticleSystem  *mParticles;
    public:
        WindArrow(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, const std::string &);
        virtual ~WindArrow();
        virtual void takeDamage(Creature &targetFrom, size_t damage);
        virtual void doDamage(Creature &targetFrom, size_t damage);
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void);
        virtual void dead(void);
        virtual void setTarget(Creature *);
    };
}

#endif //OGREGAMEPLAY_WINDARROW_H
