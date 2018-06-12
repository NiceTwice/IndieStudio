/*
** Heal.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Sun May 22 16:54:30 2016 walbecq
** Last update Tue May 31 18:49:46 2016 walbecq
*/

#ifndef OGREGAMEPLAY_HEAL_H
#define OGREGAMEPLAY_HEAL_H

#include "Spell.h"

namespace IND {
    class Heal : public Spell{
    protected:
        Ogre::ParticleSystem                          *ps;
        float                                         timer;
        Ogre::SceneNode                               *mNode;
    public:
        Heal(Creature *parent, Ogre::SceneManager *sm);
        virtual ~Heal();
        virtual void use(Creature *target);
        virtual void update(const Ogre::FrameEvent& evt);
    };

}

#endif //OGREGAMEPLAY_HEAL_H
