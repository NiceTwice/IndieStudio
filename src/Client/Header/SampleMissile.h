//
// Created by nicetwice on 11/05/16.
//

#ifndef OGREGAMEPLAY_SAMPLEMISSILE_H
#define OGREGAMEPLAY_SAMPLEMISSILE_H

#include "Creature.h"

namespace IND {
    class SampleMissile : public Creature{
            Ogre::ParticleSystem  *mParticles;
        public:
            SampleMissile(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, const std::string &particleName);
            virtual ~SampleMissile();
            virtual void takeDamage(Creature &targetFrom, size_t damage);
            virtual void doDamage(Creature &targetFrom, size_t damage);
            virtual void update(const Ogre::FrameEvent& evt);
            virtual void resetAnimation(void);
            virtual void dead(void);
            virtual void setTarget(Creature *);
        };
}

#endif //OGREGAMEPLAY_SAMPLEMISSILE_H
