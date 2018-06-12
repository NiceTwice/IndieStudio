//
// Created by debruy_p on 31/05/16.
//

#include <Server.hh>
#include <Wall.hh>

Wall::Wall(Ogre::Vector3 const &pos):_position(pos), _collideRange(245) {
    struct position buff;
    buff.x = _position.x;
    buff.y = _position.y;
    buff.z = _position.z;
    for (auto jt = Server::getSingleton().getUsers().begin(); jt != Server::getSingleton().getUsers().end(); ++jt) {
        if ((*jt)->isConnected()) {
            (*jt)->stockOrderToSend(new Order(Order::TYPE::WALL, sizeof(struct position), &buff));
        }
    }
    _minCollide = Ogre::Vector3(_position.x - _collideRange, 0, _position.z - _collideRange);
    _maxCollide = Ogre::Vector3(_position.x + _collideRange, 0, _position.z + _collideRange);
}

Wall::~Wall() {

}

void Wall::setPosition(Ogre::Vector3 const &pos) {
    _position.x = pos.x;
    _position.y = pos.y;
    _position.z = pos.z;
}

Ogre::Vector3 const &Wall::getPosition(void) const {
	return _position;
}

float Wall::getCollideRange(void) const {
	return _collideRange;
}

Ogre::Vector3 const &Wall::getMinCollide() const{
    return _minCollide;
};

Ogre::Vector3 const &Wall::getMaxCollide() const{
    return _maxCollide;
};