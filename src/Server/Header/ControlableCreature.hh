//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_CONTROLABLECREATURE_HH
#define SERVER_CONTROLABLECREATURE_HH

#include "Creature.hh"

class ControlableCreature : public Creature{
protected:
    float _respawnTime;
public:
    ControlableCreature(size_t, Ogre::Vector3 const &, size_t);
    virtual ~ControlableCreature();

    virtual void update(float timeSinceLastUpdate, std::pair<std::list<Creature *>, std::list<Wall *>> const &);
    virtual void dead();

protected:
    virtual void reSpawn();

private:
    struct resurect{
        size_t id;
        float x;
        float y;
        float z;
    };
};

#endif //SERVER_CONTROLABLECREATURE_HH