//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_SHURIKENMISSILE_HH
#define SERVER_SHURIKENMISSILE_HH


#include "Missile.hh"

class ShurikenMissile : public Missile{
protected:
    size_t  _dammage;
public:
    ShurikenMissile(Creature *by);
    virtual ~ShurikenMissile();

    void onTarget();
};


#endif //SERVER_SHURIKENMISSILE_HH
