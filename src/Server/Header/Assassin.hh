//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_ASSASSIN_HH
#define SERVER_ASSASSIN_HH


#include "ControlableCreature.hh"

class Assassin : public ControlableCreature{
protected:

public:
    Assassin(size_t, Ogre::Vector3 const &);
    virtual ~Assassin();
};


#endif //SERVER_ASSASSIN_HH