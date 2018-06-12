//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_ARCHER_HH
#define SERVER_ARCHER_HH


#include "ControlableCreature.hh"

class Archer : public ControlableCreature{
protected:

public:
    Archer(size_t, Ogre::Vector3 const &);
    virtual ~Archer();
};


#endif //SERVER_ARCHER_HH
