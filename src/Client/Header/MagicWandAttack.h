/*
** MagicWandAttack.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Fri Jun  3 17:48:54 2016 walbecq
** Last update Fri Jun  3 17:49:23 2016 walbecq
*/

#ifndef OGREGAMEPLAY_MAGICWANDATTACK_H
#define OGREGAMEPLAY_MAGICWANDATTACK_H

#include "Spell.h"

namespace IND {
    class MagicWandAttack : public Spell{
    protected:
        size_t                                        _damage;
        std::vector<Creature*>                        arrows;
    public:
        MagicWandAttack(Creature *parent, Ogre::SceneManager *sm);
        virtual ~MagicWandAttack();
        virtual void use(Creature *target);
        virtual void update(const Ogre::FrameEvent& evt);
    };

}

#endif //OGREGAMEPLAY_MAGICWANDATTACK_H
