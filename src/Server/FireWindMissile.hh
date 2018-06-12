//
// Created by debruy_p on 01/06/16.
//

#ifndef SERVER_FIREWINDMISSILE_HH
#define SERVER_FIREWINDMISSILE_HH

#include <Missile.hh>

class FireWindMissile : public Missile{
protected:
    size_t  _dammage;
public:
    FireWindMissile(Creature *by);
    virtual ~FireWindMissile();

    void onTarget();
};


#endif //SERVER_FIREWINDMISSILE_HH
