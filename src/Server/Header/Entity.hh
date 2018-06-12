//
// Created by debruy_p on 13/05/16.
//

#ifndef SERVER_ENTITY_HH
#define SERVER_ENTITY_HH

#include <OGRE/Ogre.h>
#include <chrono>

#define CHANGEDIRECTION_BUFFLEN  (sizeof(size_t) + 6 * sizeof(float))

class Entity {
protected:
    Ogre::Vector3   _position;
    Ogre::Vector3   _moveVector;
    float           _moveSpeed;
    std::chrono::time_point<std::chrono::high_resolution_clock>           _timeSinceLastSendPosition;
public:
    Entity(Ogre::Vector3 const &);
    virtual ~Entity();

    Ogre::Vector3 const &getPosition() const;
    Ogre::Vector3 const &getMoveVector() const;
    virtual float getMoveSpeed() const;

    void setPosition(Ogre::Vector3 const &);

    virtual void genBuffer(char *) const;
};

#endif //SERVER_ENTITY_HH