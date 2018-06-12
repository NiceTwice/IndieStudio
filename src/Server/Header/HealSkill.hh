//
// Created by debruy_p on 19/05/16.
//

#ifndef SERVER_HEALSKILL_HH
#define SERVER_HEALSKILL_HH


#include "Skill.hh"

class HealSkill : public Skill{
protected:
    size_t _heal;
public:
    HealSkill(Creature *parent);
    virtual ~HealSkill();

    void useOn(Creature *);

};


#endif //SERVER_HEALSKILL_HH
