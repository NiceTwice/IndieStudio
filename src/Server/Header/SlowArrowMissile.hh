//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_SLOWARROWMISSILE_HH
#define SERVER_SLOWARROWMISSILE_HH


#include "Missile.hh"

class SlowArrowMissile : public Missile{
protected:
    size_t  _dammage;
public:
    SlowArrowMissile(Creature *by);
    virtual ~SlowArrowMissile();

    void onTarget();
};


#endif //SERVER_SLOWARROWMISSILE_HH
