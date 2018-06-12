//
// Created by debruy_p on 08/05/16.
//

#ifndef TESTCEGUI_ORDER_HH
#define TESTCEGUI_ORDER_HH

#include <stddef.h>
#include "Profile.hh"

class Order {
public:
    enum TYPE {
        NOTHING,
        HEY,
        PING,
        DECONNECT,
        MDP,
        PROFIL,
        HOST,
        CHAT,
        READY,
        STARTGAME,
        NEW_CREATURE,
        RightButtonClick,
        ChangeCreatureDirection,
        SetCreatureToControl,
        UseSpell,
        SetHpMp,
        SetCreatureDeath,
        SetErrorMessage,
        RespawnCreature,
        SetBuffOnCreature,
        ChangeCharac,
        addWorldObject
    };
    typedef struct  order{
        Order::TYPE *type;
        size_t      *size;
        void        *data;
    }               t_order;
protected:
    size_t _size;
    void *_data;
public:
    Order(TYPE, size_t, void *);
    virtual ~Order();

    size_t getSize() const;
    void *getData() const;
    Order::TYPE getType() const;

private:

};


#endif //TESTCEGUI_ORDER_HH
