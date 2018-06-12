//
// Created by debruy_p on 27/04/16.
//

#ifndef SERVER_ORDER_HH
#define SERVER_ORDER_HH

#include <stddef.h>

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
        CREATURE,
        MOVETO,
        CHANGE_DIRECTION,
        YOU_CONTROL,
        USE_SKILL,
        DAMMAGE,
        DEAD,
        ERROR_MSG,
        RESPAWN,
        APPLY_BUFF,
        CHARACTER,
        WALL
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
    struct t_orderInfo
    {
        size_t type;
        size_t size;
    };
};

#endif //SERVER_ORDER_HH