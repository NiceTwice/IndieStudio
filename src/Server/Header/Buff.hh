//
// Created by debruy_p on 18/05/16.
//

#ifndef SERVER_BUFF_HH
#define SERVER_BUFF_HH

#include <cstddef>

class Buff {
public:
    enum TYPE: size_t{
        SPEEDBOOST,
        SLOWBOOST,
        ARMUREBUFF,
        INFIRE
    };
protected:
    size_t _type;
    float _life;
    float _mana;
    float _force;
    float _armure;
    float _speed;
    size_t _dammage;
    float _time;
public:
    virtual ~Buff();

    virtual size_t getType() const;
    virtual float getLifeMul() const;
    virtual float getManaMul() const;
    virtual float getForceMul() const;
    virtual float getArmureMul() const;
    virtual float getSpeedMul() const;
    virtual size_t getDammage() const;

    virtual void update(float timeSinceLastUpdate);
    virtual bool isDead() const;
};

#endif //SERVER_BUFF_HH
