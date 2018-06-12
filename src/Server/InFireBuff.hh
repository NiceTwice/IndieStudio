//
// Created by debruy_p on 01/06/16.
//

#ifndef SERVER_INFIREBUFF_HH
#define SERVER_INFIREBUFF_HH

#include <Buff.hh>

class InFireBuff : public Buff{
protected:
    Creature *_target;
    float t;
public:
    InFireBuff(Creature *target);
    virtual ~InFireBuff();

    virtual void update(float timeSinceLastUpdate);
};


#endif //SERVER_INFIREBUFF_HH