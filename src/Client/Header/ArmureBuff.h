/*
** ArmureBuff.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Tue May 31 18:26:24 2016 walbecq
** Last update Tue May 31 18:26:54 2016 walbecq
*/

#ifndef OGREGAMEPLAY_ARMUREBUFF_H
#define OGREGAMEPLAY_ARMUREBUFF_H

#include "Buff.h"

namespace IND {
    class ArmureBuff : public Buff{
        Ogre::ParticleSystem   *_partSystem;
        float                   addedValue;
        Ogre::SceneNode         *node;
    public:
        ArmureBuff();
        virtual ~ArmureBuff();
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void setTarget(Creature *);
    };
}

#endif //OGREGAMEPLAY_ARMUREBUFF_H
