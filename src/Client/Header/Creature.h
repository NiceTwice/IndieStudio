//
// Created by nicetwice on 08/05/16.
//

#ifndef OGREGAMEPLAY_CREATURE_H
#define OGREGAMEPLAY_CREATURE_H

#include "Entity.h"
#include "Spell.h"
#include "Buff.h"

std::string         getParticleSystemNextName(void);
namespace IND {
    class Spell;
    class Buff;

    class Creature : public Entity {
    protected:
        Creature                   *_target;
        size_t                      _maxHp;
        size_t                      _maxMp;
        size_t                      _hp;
        size_t                      _mp;
        size_t                      _attackDamage;
        Ogre::Vector3               _moveTo;
        bool                        _chaseTarget;
        float                       _mWalkSpeed;
        float                       _basicWalkSpeed;
        Ogre::Vector3               _mDirection;
        bool                        _isDead;
        bool                        _isMooving;
        Ogre::AnimationState        *currentAnimation;

        float                       correctionSpeed;
        Ogre::Vector3               correctionPosition;
        std::vector<Spell*>         _spells;
        std::list<Buff*>            _buffs;

        std::string                 currentHpStr;
        std::string                 currentMpstr;
        float                       _deathTimer;
    public:
        Creature(const Ogre::Vector3 &position, Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id);
        virtual ~Creature();
        virtual void takeDamage(Creature &targetFrom, size_t damage) = 0;
        virtual void doDamage(Creature &targetFrom, size_t damage) = 0;
        virtual void update(const Ogre::FrameEvent& evt);
        virtual void resetAnimation(void) = 0;
        virtual void setTarget(Creature *);

        void treatPositionAndDirection(Ogre::Vector3 const &dir, Ogre::Vector3 const &pos);
        void setPosition(Ogre::Vector3 const &);
        void setMoveTo(const Ogre::Vector3 &);
        void setMoveTo(float x, float y, float z);
        void respawnIt(const Ogre::Vector3 &);
        void setDirection(const Ogre::Vector3 &);
        void setAnimationState(Ogre::AnimationState *state);

        virtual void dead(void);
        virtual void setChaseTarget(bool);
        virtual bool isMooving(void);

        virtual void learnSpell(Spell *spell);
        virtual void useSpell(size_t spellType, Creature *target);

        void        addBuff(Buff *);
        size_t      getHp(void) const;
        size_t      getMaxHp(void) const;
        size_t      getMp(void) const;
        size_t      getMaxMp(void) const;
        bool        isDead(void) const;
        float       getWalkSpeed(void) const;
        float       getBasicWalkSpeed(void) const;
        void        setWalkSpeed(float speed);

        size_t      getSceneId(void) const;

        Spell  *getSpellByNumber(size_t nb) const;

        void        setCurrentMp(size_t const value);
        void        setCurrentHp(size_t const value);
        void        setMaxHp(size_t const value);
        void        setMaxMp(size_t const value);
        std::string const &getCurrentHpStr() const;
        std::string const &getCurrentMpStr() const;
        float       getDeathTimer() const;
    };
}


#endif //OGREGAMEPLAY_CREATURE_H
