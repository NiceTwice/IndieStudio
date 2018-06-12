//
// Created by debruy_p on 13/05/16.
//

#include "Entity.hh"
#include "Server.hh"

Entity::Entity(Ogre::Vector3 const &position):_position(position), _moveVector(0, 0, 0), _moveSpeed(250), _timeSinceLastSendPosition(Server::getSingleton().getTimeMillis()) {

}

Entity::~Entity() {

}

Ogre::Vector3 const &Entity::getPosition() const {
    return _position;
}

Ogre::Vector3 const &Entity::getMoveVector() const {
    return _moveVector;
}

float Entity::getMoveSpeed() const {
    return _moveSpeed;
}

void Entity::genBuffer(char *) const {

}

void Entity::setPosition(Ogre::Vector3 const &pos) {
    _position = pos;
}