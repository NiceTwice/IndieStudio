//
// Created by nicetwice on 10/05/16.
//

#ifndef OGREGAMEPLAY_BUFF_H
#define OGREGAMEPLAY_BUFF_H

#include "Creature.h"

namespace IND {
    class Creature;
    class Buff{
    protected:
        Creature        *_parent;
        float           _duration;
        bool            _isEnded;
    public:
        enum TYPE : size_t{
	  SpeedBoost = 0,
            SlowBoost,
	    Armure,
	    FireBuff
        };
        Buff();
        virtual ~Buff();
        virtual void update(const Ogre::FrameEvent& evt) = 0;
        virtual bool isEnded(void) const;
        virtual void setTarget(Creature *) = 0;
    };
}

#endif //OGREGAMEPLAY_BUFF_H
