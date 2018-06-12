//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_SPEEDBOOSTSKILL_HH
#define SERVER_SPEEDBOOSTSKILL_HH


#include "Skill.hh"

class SpeedBoostSkill : public Skill{
protected:

public:
    SpeedBoostSkill(Creature *parent);
    virtual ~SpeedBoostSkill();

    void useOn(Creature *);
};


#endif //SERVER_SPEEDBOOSTSKILL_HH
