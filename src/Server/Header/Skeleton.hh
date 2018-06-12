//
// Created by debruy_p on 13/05/16.
//

#ifndef SERVER_SKELETON_HH
#define SERVER_SKELETON_HH

#include "ControlableCreature.hh"

class Skeleton : public ControlableCreature{
protected:

public:
    Skeleton(size_t, Ogre::Vector3 const &);
    virtual ~Skeleton();
};

#endif //SERVER_SKELETON_HH