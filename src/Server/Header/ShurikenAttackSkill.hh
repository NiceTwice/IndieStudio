//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_SHURIKENATTACKSKILL_HH
#define SERVER_SHURIKENATTACKSKILL_HH


#include "Skill.hh"
#include "Missile.hh"

class ShurikenAttackSkill : public Skill{
protected:
    std::vector<Missile*>   _arrows;
public:
    ShurikenAttackSkill(Creature *parent);
    virtual ~ShurikenAttackSkill();

    virtual void useOn(Creature *);
    void update(float timeSinceLastUpdate);

};


#endif //SERVER_SHURIKENATTACKSKILL_HH
