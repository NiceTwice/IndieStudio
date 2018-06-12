//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_FIREBALLMISSILE_HH
#define SERVER_FIREBALLMISSILE_HH


#include "Missile.hh"

class FireballMissile : public Missile{
protected:
    size_t  _dammage;
public:
    FireballMissile(Creature *by);
    virtual ~FireballMissile();

    void onTarget();

};


#endif //SERVER_FIREBALLMISSILE_HH
