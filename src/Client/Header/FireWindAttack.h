/*
** FireWindAttack.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Tue May 31 17:57:44 2016 walbecq
** Last update Tue May 31 17:58:08 2016 walbecq
*/

#ifndef OGREGAMEPLAY_FIREWINDATTACK_H
#define OGREGAMEPLAY_FIREWINDATTACK_H

#include "Creature.h"

namespace IND {
        class FireWindAttack : public Spell {
            std::vector<Creature*>                  arrows;
        public:
            FireWindAttack(Creature *parent, Ogre::SceneManager *sm);
            virtual ~FireWindAttack();
            virtual void use(Creature *target);
            virtual void update(const Ogre::FrameEvent& evt);
        };
}

#endif //OGREGAMEPLAY_FIREWINDATTACK_H
