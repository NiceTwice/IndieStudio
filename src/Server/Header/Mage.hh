//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_MAGE_HH
#define SERVER_MAGE_HH


#include "ControlableCreature.hh"

class Mage : public ControlableCreature{
protected:

public:
    Mage(size_t, Ogre::Vector3 const &);
    virtual ~Mage();
};


#endif //SERVER_MAGE_HH
