//
// Created by nicetwice on 08/05/16.
//

#ifndef OGREGAMEPLAY_BODYATTACK_H
#define OGREGAMEPLAY_BODYATTACK_H

#include "Spell.h"
#include "GameMenu.hh"

namespace IND {
    class BodyAttack : public Spell{
        std::vector<std::string>        _animList;
    public:
        BodyAttack(Creature *parent, Ogre::SceneManager *sm, const std::string &);
        virtual ~BodyAttack();
        virtual void use(Creature *target);
        virtual void update(const Ogre::FrameEvent& evt);
    };
}

#endif //OGREGAMEPLAY_BODYATTACK_H
