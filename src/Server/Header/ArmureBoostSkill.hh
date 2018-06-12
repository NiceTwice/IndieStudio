//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_ARMUREBOOSTSKILL_HH
#define SERVER_ARMUREBOOSTSKILL_HH


#include "Skill.hh"

class ArmureBoostSkill : public Skill{
protected:

public:
    ArmureBoostSkill(Creature *parent);
    virtual ~ArmureBoostSkill();

    void useOn(Creature *);

};


#endif //SERVER_ARMUREBOOSTSKILL_HH
