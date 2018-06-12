//
// Created by debruy_p on 01/06/16.
//

#ifndef SERVER_FIREWINDSKILL_HH
#define SERVER_FIREWINDSKILL_HH

#include <Skill.hh>
#include <Missile.hh>

class FireWindSkill : public Skill{
protected:
    std::vector<Missile*>   _arrows;
public:
    FireWindSkill(Creature *parent);
    virtual ~FireWindSkill();

    virtual void useOn(Creature *);
    void update(float timeSinceLastUpdate);

};


#endif //SERVER_FIREWINDSKILL_HH
