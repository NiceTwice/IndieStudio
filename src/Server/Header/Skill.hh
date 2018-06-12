//
// Created by debruy_p on 14/05/16.
//

#ifndef SERVER_SKILL_HH
#define SERVER_SKILL_HH

#include <cstddef>
#include "Creature.hh"

#define SKILL_BUFFLEN   (3 * sizeof(size_t))

class Creature;

class Skill {
public:
    enum TYPE : size_t{
        MELEE_ATTACK,
        BOW_ATTACK,
        SPEEDBOOSTBUFF,
        SLOWARROW,
        ARMUREBUFF,
        HEAL,
        SHURIKEN,
        FIREBALL,
        MAGICWAND,
        FIREWIND,
    };
protected:
    TYPE    _type;
    float   _cooldown;
    float   _currentCoolDown;
    size_t  _manaCost;
    Creature* _parent;
    float     _range;
public:
    Skill(Skill::TYPE, Creature *);
    virtual ~Skill();

    virtual void useOn(Creature *) = 0;

    virtual size_t getType() const;
    virtual bool isReady() const;
    virtual bool isOnRange(Creature *target) const;
    virtual bool haveEnouthMana() const;

    virtual void update(float timeSinceLastUpdate);
protected:
    virtual void sendUseSkill(Creature *target) const;
private:
    struct skillInfo {
        size_t type;
        size_t by;
        size_t to;
    };
};

#endif //SERVER_SKILL_HH