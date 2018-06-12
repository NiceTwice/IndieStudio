/*
** SlowWindAttack.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Tue May 31 12:55:35 2016 walbecq
** Last update Tue May 31 12:58:25 2016 walbecq
*/

#ifndef OGREGAMEPLAY_SLOWWINDATTACK_H
#define OGREGAMEPLAY_SLOWWINDATTACK_H

#include "Creature.h"

namespace IND {
        class SlowWindAttack : public Spell {
            std::vector<Creature*>                  arrows;
        public:
            SlowWindAttack(Creature *parent, Ogre::SceneManager *sm);
            virtual ~SlowWindAttack();
            virtual void use(Creature *target);
            virtual void update(const Ogre::FrameEvent& evt);
        };
}

#endif //OGREGAMEPLAY_SLOWWINDATTACK_H
