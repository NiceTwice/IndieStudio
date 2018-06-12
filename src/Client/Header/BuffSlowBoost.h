/*
** BuffSlowBoost.h for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/testCEGUI
** 
** Made by walbecq
** Login   <hugo@epitech.net>
** 
** Started on  Thu May 26 18:55:44 2016 walbecq
** Last update Thu May 26 18:56:35 2016 walbecq
*/

#ifndef OGREGAMEPLAY_BUFFSLOWBOOST_H
#define OGREGAMEPLAY_BUFFSLOWBOOST_H

#include "Buff.h"

namespace IND {
    class BuffSlowBoost : public Buff{
        Ogre::ParticleSystem   *_partSystem;
        float                   addedValue;
    public:
        BuffSlowBoost();
        virtual ~BuffSlowBoost();
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void setTarget(Creature *);
    };
}

#endif //OGREGAMEPLAY_BUFFSLOWBOOST_H
