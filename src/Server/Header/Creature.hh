//
// Created by debruy_p on 13/05/16.
//

#ifndef SERVER_CREATURE_HH
#define SERVER_CREATURE_HH

#include "Entity.hh"
#include "Skill.hh"
#include "Profile.hh"
#include "Buff.hh"
#include "Wall.hh"

class Skill;

class User;

class Creature : public Entity{
public:
    enum TYPE : size_t{
        SKELETON,
        WARRIOR,
        ARCHER,
        MAGE,
        ASSASSIN,
        PRIEST
    };
protected:
    size_t        _id;
    TYPE          _type;
    Ogre::Vector3 _moveTo;
    float         _distanceTo;
    size_t        _maxHp;
    size_t        _maxMp;
    size_t        _hp;
    size_t        _mp;
    size_t        _force;
    size_t        _armure;
    size_t        _spirit;
    bool          _dead;
    std::vector<Skill*> _skills;
    std::list<Buff*>    _buffs;
    float           _regenTime;
    float           _collideRange;
    Creature        *_target;
    float           _lastMove;
    bool            _isEnnemy;
public:
    Creature(size_t, Ogre::Vector3 const &, size_t);
    virtual ~Creature();

    virtual void update(float timeSinceLastUpdate, std::pair<std::list<Creature *>, std::list<Wall *>> const &);
    virtual void ai(float timeSinceLastUpdate, std::vector<Creature*> const &list);

    virtual bool collideCreature(std::list<Creature*> const &list, Creature*);
    virtual bool collideWall(std::list<Wall*> const &list);

    size_t getId() const;
    virtual size_t getLife() const;
    virtual size_t getMaxLife() const;
    virtual size_t getMana() const;
    virtual size_t getMaxMana() const;
    virtual bool isDead() const;
    virtual size_t getForce() const;
    virtual size_t getArmure() const;
    virtual float  getSpeed() const;
    virtual float getCollideRange() const;

    virtual void moveTo(Ogre::Vector3 const &);
    virtual void changeDirection(Ogre::Vector3 const &dir);
    virtual void syncronize();

    virtual void takeDammage(size_t);
    virtual void heal(size_t);
    virtual void consumeMana(size_t);
    virtual void regenMana(size_t);

    virtual void useSkill(User *, size_t, Creature *);
    virtual void addBuff(Buff *);

    virtual void dead();

    virtual void controledBy(User *) const;

    virtual bool isEnnemy() const;
    virtual void setAlly();
protected:
    virtual void sendPosition() const;
    virtual void sendLifeMana() const;
    virtual void sendSpawn() const;
    virtual void sendBuff() const;
private:
    struct creatureInfo{
        size_t type;
        size_t id;
        float xPosition;
        float yPosition;
        float zPosition;
        size_t life;
        size_t mana;
    };
    struct changeDiretion{
        size_t id;
        float xPos;
        float yPos;
        float zPos;
        float xMove;
        float yMove;
        float zMove;
    };
    struct dammage{
        size_t id;
        size_t life;
        size_t mana;
    };
    struct allyInfo {
        size_t id;
        char name[PROFILELEN];
    };
    struct buffInfo {
        size_t targetId;
        size_t type;
    };
};

#endif //SERVER_CREATURE_HH