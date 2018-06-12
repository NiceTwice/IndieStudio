//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_MAGICWANDSKILL_HH
#define SERVER_MAGICWANDSKILL_HH


#include "Skill.hh"
#include "Missile.hh"

class MagicWandSkill : public Skill{
protected:
    std::vector<Missile*>   _arrows;
public:
    MagicWandSkill(Creature *parent);
    virtual ~MagicWandSkill();

    virtual void useOn(Creature *);
    void update(float timeSinceLastUpdate);

};


#endif //SERVER_MAGICWANDSKILL_HH
