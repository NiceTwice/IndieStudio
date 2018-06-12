//
// Created by debruy_p on 14/05/16.
//

#ifndef SERVER_MISSILE_HH
#define SERVER_MISSILE_HH

#include "Entity.hh"
#include "Creature.hh"

class Missile : public Entity{
public:
    enum TYPE {
        ARROW,
        SLOWARROW,
        SHURIKEN,
        FIREBALL,
        MAGICWAND,
        FIREWIND
    };
protected:
    TYPE            _type;
    Creature *      _origin;
    Creature *      _target;
    bool            _used;
public:
    Missile(Missile::TYPE, Creature *by);
    virtual ~Missile();

    Missile::TYPE getType() const;
    Creature *getOrigin() const;
    Creature *getTarget() const;

    void launchIn(Creature *);
    bool isUsed() const;

    virtual void update(float timeSinceLastUpdate);
    virtual void onTarget() = 0;
};

#endif //SERVER_MISSILE_HH