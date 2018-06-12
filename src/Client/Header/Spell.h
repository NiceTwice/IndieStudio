//
// Created by nicetwice on 08/05/16.
//

#ifndef OGREGAMEPLAY_SPELL_H
#define OGREGAMEPLAY_SPELL_H

#include "Creature.h"


namespace IND {
    class Creature;


    class Spell {
    public:
        enum Type : size_t{
            MeleeAttack,
            RangeAttack,
            SpeedBoost,
	      SlowWindArrow,
	      ArmureBuff,
	      Heal,
	      Shuriken,
	      FireBall,
	      MagicWand,
	      FireWindAttack
		};
    protected:
        Creature            *_parent;
        Ogre::SceneManager  *mSceneManager;
        Type                _type;
		float				_cd;
		float				_currentCd;
		std::string			_imageName;
    public:
        Spell(Creature *parent, Ogre::SceneManager *sm);
        virtual ~Spell();
		virtual float getCurrentCd(void) const;
		virtual float getMaxCd(void) const;
        virtual void use(Creature *target);
        virtual void update(const Ogre::FrameEvent& evt) = 0;

		virtual std::string const &getImageName(void) const;
		virtual void		updateCd(const Ogre::FrameEvent &evt);
        Spell::Type  getType(void) const;
    };
}

#endif //OGREGAMEPLAY_SPELL_H
