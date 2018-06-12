//
// Created by nicetwice on 10/05/16.
//

#ifndef OGREGAMEPLAY_BUFFSPEEDBOOSTFIRE_H
#define OGREGAMEPLAY_BUFFSPEEDBOOSTFIRE_H

#include "Buff.h"

namespace IND {
    class BuffSpeedBoostFire : public Buff{
        Ogre::ParticleSystem   *_partSystem;
        float                   addedValue;
    public:
        BuffSpeedBoostFire();
        virtual ~BuffSpeedBoostFire();
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void setTarget(Creature *);
    };
}

#endif //OGREGAMEPLAY_BUFFSPEEDBOOSTFIRE_H
