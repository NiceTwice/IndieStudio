//
// Created by debruy_p on 31/05/16.
//

#ifndef SERVER_WALL_HH
#define SERVER_WALL_HH

#include <OGRE/OgreVector3.h>

class Wall {
protected:
    Ogre::Vector3 _position;
    float _collideRange;
    Ogre::Vector3 _minCollide;
    Ogre::Vector3 _maxCollide;
public:
    Wall(Ogre::Vector3 const &);
    virtual ~Wall();
    Ogre::Vector3 const &getPosition(void) const;
    void setPosition(Ogre::Vector3 const &);
    float getCollideRange(void) const;
    Ogre::Vector3 const &getMinCollide() const;
    Ogre::Vector3 const &getMaxCollide() const;
private:
    struct position
    {
        float x;
        float y;
        float z;
    };
};


#endif //SERVER_WALL_HH