//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_SLOWARROWSKILL_HH
#define SERVER_SLOWARROWSKILL_HH


#include "Skill.hh"
#include "Missile.hh"

class SlowArrowSkill : public Skill{
protected:
    std::vector<Missile*>   _arrows;
public:
    SlowArrowSkill(Creature *parent);
    virtual ~SlowArrowSkill();

    virtual void useOn(Creature *);
    void update(float timeSinceLastUpdate);

};


#endif //SERVER_SLOWARROWSKILL_HH
