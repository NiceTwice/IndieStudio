//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_FIREBALLSKILL_HH
#define SERVER_FIREBALLSKILL_HH


#include "Skill.hh"
#include "Missile.hh"

class FireballSkill : public Skill{
protected:
    std::vector<Missile*>   _arrows;
public:
    FireballSkill(Creature *parent);
    virtual ~FireballSkill();

    virtual void useOn(Creature *);
    void update(float timeSinceLastUpdate);
};


#endif //SERVER_FIREBALLSKILL_HH
