//
// Created by debruy_p on 14/05/16.
//

#ifndef SERVER_BOWATTACKSKILL_HH
#define SERVER_BOWATTACKSKILL_HH

#include "Skill.hh"
#include "Creature.hh"
#include "Missile.hh"

class BowAttackSkill : public Skill{
protected:
    std::vector<Missile*>   _arrows;
public:
    BowAttackSkill(Creature *parent);
    virtual ~BowAttackSkill();

    virtual void useOn(Creature *);
    void update(float timeSinceLastUpdate);
};


#endif //SERVER_BOWATTACKSKILL_HH
