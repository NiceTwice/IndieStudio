//
// Created by debruy_p on 30/05/16.
//

#ifndef SERVER_CREATUREFACTORY_HH
#define SERVER_CREATUREFACTORY_HH


#include <Creature.hh>

class CreatureFactory {
protected:

public:
    static Creature *createCreature(Creature::TYPE type, Ogre::Vector3 const &pos, size_t id);
};


#endif //SERVER_CREATUREFACTORY_HH
