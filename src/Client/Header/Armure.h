/*
** Armure.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Tue May 31 18:48:45 2016 walbecq
** Last update Tue May 31 18:49:10 2016 walbecq
*/

#ifndef OGREGAMEPLAY_ARMURE_H
#define OGREGAMEPLAY_ARMURE_H

#include "Spell.h"

namespace IND {
    class Armure : public Spell{
    protected:
        Ogre::ParticleSystem                          *ps;
        float                                         timer;
        Ogre::SceneNode                               *mNode;
    public:
        Armure(Creature *parent, Ogre::SceneManager *sm);
        virtual ~Armure();
        virtual void use(Creature *target);
        virtual void update(const Ogre::FrameEvent& evt);
    };

}

#endif //OGREGAMEPLAY_ARMURE_H
