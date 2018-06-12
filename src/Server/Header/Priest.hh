//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_PRIEST_HH
#define SERVER_PRIEST_HH


#include "ControlableCreature.hh"

class Priest : public ControlableCreature{
protected:

public:
    Priest(size_t, Ogre::Vector3 const &);
    virtual ~Priest();
};


#endif //SERVER_PRIEST_HH
