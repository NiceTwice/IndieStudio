//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_WARRIOR_HH
#define SERVER_WARRIOR_HH


#include "ControlableCreature.hh"

class Warrior : public ControlableCreature{
protected:

public:
    Warrior(size_t, Ogre::Vector3 const &);
    virtual ~Warrior();
};


#endif //SERVER_WARRIOR_HH
