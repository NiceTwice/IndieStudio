//
// Created by debruy_p on 14/05/16.
//

#ifndef SERVER_ARROWMISSILE_HH
#define SERVER_ARROWMISSILE_HH


#include "Missile.hh"

class ArrowMissile : public Missile{
protected:
    size_t  _dammage;
public:
    ArrowMissile(Creature *by);
    virtual ~ArrowMissile();

    void onTarget();
};


#endif //SERVER_ARROWMISSILE_HH
