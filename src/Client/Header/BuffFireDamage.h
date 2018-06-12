/*
** BuffFireDamage.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Tue May 31 17:56:36 2016 walbecq
** Last update Wed Jun  1 15:46:51 2016 walbecq
*/

#ifndef OGREGAMEPLAY_BUFFFIREDAMAGE_H
#define OGREGAMEPLAY_BUFFFIREDAMAGE_H

#include "Buff.h"

namespace IND {
    class BuffFireDamage : public Buff{
        Ogre::ParticleSystem   *_partSystem;
        float                   addedValue;
        Ogre::SceneNode         *node;
    public:
        BuffFireDamage();
        virtual ~BuffFireDamage();
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void setTarget(Creature *);
    };
}

#endif //OGREGAMEPLAY_BUFFFIREDAMAGE_H
