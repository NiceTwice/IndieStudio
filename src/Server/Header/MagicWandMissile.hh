//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_MAGICWANDMISSILE_HH
#define SERVER_MAGICWANDMISSILE_HH


#include "Missile.hh"

class MagicWandMissile : public Missile{
protected:
    size_t  _dammage;
public:
    MagicWandMissile(Creature *by);
    virtual ~MagicWandMissile();

    void onTarget();

};


#endif //SERVER_MAGICWANDMISSILE_HH
