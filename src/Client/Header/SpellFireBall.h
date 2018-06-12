//
// Created by nicetwice on 11/05/16.
//

#ifndef OGREGAMEPLAY_SPELLFIREBALL_H
#define OGREGAMEPLAY_SPELLFIREBALL_H

#include "Spell.h"

namespace IND {
    class SpellFireBall : public Spell{
    protected:
        size_t                                        _damage;
        std::vector<Creature*>                        arrows;
    public:
        SpellFireBall(Creature *parent, Ogre::SceneManager *sm);
        virtual ~SpellFireBall();
        virtual void use(Creature *target);
        virtual void update(const Ogre::FrameEvent& evt);
    };

}

#endif //OGREGAMEPLAY_SPELLFIREBALL_H
