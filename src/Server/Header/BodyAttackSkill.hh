//
// Created by debruy_p on 14/05/16.
//

#ifndef SERVER_BODYATTACKSKILL_HH
#define SERVER_BODYATTACKSKILL_HH


#include "Skill.hh"

class BodyAttackSkill : public Skill{
protected:

public:
    BodyAttackSkill(Creature *parent);
    virtual ~BodyAttackSkill();

    void useOn(Creature *);
};


#endif //SERVER_BODYATTACKSKILL_HH
