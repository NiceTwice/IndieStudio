//
// Created by debruy_p on 13/05/16.
//

#include <Wall.hh>
#include "Creature.hh"
#include "Order.hh"
#include "Server.hh"

Creature::Creature(size_t id, Ogre::Vector3 const &position, size_t type):Entity(position), _id(id), _type((TYPE)type), _moveTo(_position),_distanceTo(0), _maxHp(10), _maxMp(10), _hp(_maxHp), _mp(_maxMp), _force(2), _armure(1), _dead(false), _skills(), _buffs(), _regenTime(0), _spirit(5), _collideRange(35) {
    _target = NULL;
    _lastMove = 0.0f;
    _isEnnemy = true;
}

Creature::~Creature() {
    for (auto it = _skills.begin(); it != _skills.end() ; ++it) {
        delete (*it);
    }
    _skills.clear();
}

size_t Creature::getId() const {
    return _id;
}

void Creature::takeDammage(size_t dammage) {

    if (dammage < getArmure())
        dammage = 0;
    else
        dammage -= getArmure();
    if (_hp <= dammage) {
        _hp = 0;
        dead();
    }
    else
        _hp -= dammage;
    sendLifeMana();
}

void Creature::heal(size_t life) {
    _hp += life;
    if (_hp > getMaxLife())
        _hp = getMaxLife();
    sendLifeMana();
}

size_t Creature::getLife() const {
    return _hp;
}

void Creature::consumeMana(size_t mana) {
    _mp -= mana;
    sendLifeMana();
}

void Creature::regenMana(size_t mana) {
    if (!_dead && _maxMp != _mp) {
        _mp += mana;
        if (_mp > getMaxMana())
            _mp = getMaxMana();
        sendLifeMana();
    }
}

size_t Creature::getMana() const {
    return _mp;
}

bool Creature::isDead() const {
    return _dead;
}

size_t Creature::getForce() const {
    size_t force = _force;
    for (auto it = _buffs.begin(); it != _buffs.end() ; ++it) {
        force *= (*it)->getForceMul();
    }
    return force;
}

size_t Creature::getArmure() const {
    size_t armure = _armure;
    for (auto it = _buffs.begin(); it != _buffs.end() ; ++it) {
        armure *= (*it)->getArmureMul();
    }
    return armure;
}

size_t Creature::getMaxLife() const {
    size_t maxLife = _maxHp;
    for (auto it = _buffs.begin(); it != _buffs.end() ; ++it) {
        maxLife *= (*it)->getLifeMul();
    }
    return maxLife;
}

size_t Creature::getMaxMana() const {
    size_t maxMana = _maxMp;
    for (auto it = _buffs.begin(); it != _buffs.end() ; ++it) {
        maxMana *= (*it)->getManaMul();
    }
    return maxMana;
}

float Creature::getSpeed() const {
    float speed = _moveSpeed;
    for (auto it = _buffs.begin(); it != _buffs.end() ; ++it) {
        speed += (_moveSpeed * (*it)->getSpeedMul()) - _moveSpeed;
    }
    if (speed < 0.0f)
        return (0.0f);
    return speed;
}

float Creature::getCollideRange() const {
    return _collideRange;
}

void Creature::moveTo(Ogre::Vector3 const & to) {
    _moveTo = to;
    _distanceTo = (_moveTo - _position).normalise();
    Ogre::Vector3 vectorDirection((_moveTo - _position).normalisedCopy());
    changeDirection(vectorDirection);
}

void Creature::changeDirection(Ogre::Vector3 const &dir) {
    if (_moveVector != dir){
        _moveVector = dir;
        sendPosition();
    }
}

void Creature::sendPosition() const{
    char buff[CHANGEDIRECTION_BUFFLEN];
    ((changeDiretion*)buff)->id = _id;
    ((changeDiretion*)buff)->xPos = _position.x;
    ((changeDiretion*)buff)->yPos = _position.y;
    ((changeDiretion*)buff)->zPos = _position.z;
    ((changeDiretion*)buff)->xMove = _moveVector.x;
    ((changeDiretion*)buff)->yMove = _moveVector.y;
    ((changeDiretion*)buff)->zMove = _moveVector.z;
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
        if ((*it)->isConnected()){
            (*it)->stockOrderToSend(new Order(Order::TYPE::CHANGE_DIRECTION, CHANGEDIRECTION_BUFFLEN, buff));
        }
    }
}
void Creature::syncronize() {
    if (Server::getSingleton().diffTime(Server::getSingleton().getTimeMillis(), _timeSinceLastSendPosition) >= 0.5) {
        if (_moveVector != Ogre::Vector3::ZERO) {
            sendPosition();
        }
        _timeSinceLastSendPosition = Server::getSingleton().getTimeMillis();
    }
}

void Creature::useSkill(User *user, size_t type, Creature *target) {
    if (target == NULL) {
        return;
    }
    for (auto it = _skills.begin(); it != _skills.end() ; ++it) {
        if ((*it)->getType() == type)
        {
            if (target->isDead()) {
                std::string msg("Your target is dead...");
                if (user)
                    user->stockOrderToSend(new Order(Order::TYPE::ERROR_MSG, msg.size() + 1, (void*)msg.c_str()));
            }
            else if (!(*it)->isReady()) {
                std::string msg("This skill is not yet ready...");
                if (user)
                    user->stockOrderToSend(new Order(Order::TYPE::ERROR_MSG, msg.size() + 1, (void*)msg.c_str()));
            }
            else if (!(*it)->haveEnouthMana()) {
                std::string msg("Not enouth mana...");
                if (user)
                    user->stockOrderToSend(new Order(Order::TYPE::ERROR_MSG, msg.size() + 1, (void*)msg.c_str()));
            }
            else if (!(*it)->isOnRange(target)) {
                std::string msg("Your target is too far...");
                if (user)
                    user->stockOrderToSend(new Order(Order::TYPE::ERROR_MSG, msg.size() + 1, (void*)msg.c_str()));
            }
            else
                (*it)->useOn(target);

            return ;
        }
    }
}

void Creature::addBuff(Buff *buff) {
    _buffs.push_back(buff);
    sendLifeMana();
    sendBuff();
}

void Creature::dead() {
    _dead = true;
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end(); ++it) {
        if ((*it)->isConnected()) {
            (*it)->stockOrderToSend(new Order(Order::TYPE::DEAD, sizeof(size_t), &_id));
        }
    }
    _moveTo = _position;
}

void Creature::sendLifeMana() const {
    dammage buff;
    buff.id = _id;
    buff.life = _hp;
    buff.mana = _mp;
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
        if ((*it)->isConnected()) {
            (*it)->stockOrderToSend(new Order(Order::TYPE::DAMMAGE, sizeof(dammage), &buff));
        }
    }
}

void Creature::sendSpawn() const {
    creatureInfo buff;
    buff.type = _type;
    buff.id = _id;
    buff.xPosition = _position.x;
    buff.yPosition = _position.y;
    buff.zPosition = _position.z;
    buff.life = _hp;
    buff.mana = _mp;
    for (auto jt = Server::getSingleton().getUsers().begin(); jt != Server::getSingleton().getUsers().end(); ++jt) {
        if ((*jt)->isConnected()) {
            (*jt)->stockOrderToSend(new Order(Order::TYPE::CREATURE, sizeof(buff), &buff));
        }
    }
}

void Creature::controledBy(User *user) const {
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
        if ((*it)->isConnected()) {
            if ((*it) == user) {
                size_t id = _id;
                user->stockOrderToSend(new Order(Order::TYPE::YOU_CONTROL, sizeof(id), &id));
            }
            else {
                allyInfo allyBuff;
                allyBuff.id = _id;
                int i = 0;
                while (i < user->getProfile().getName().size()) {
                    (allyBuff.name)[i] = (user->getProfile().getName().c_str())[i];
                    i++;
                }
                (allyBuff.name)[i] = 0;
                (*it)->stockOrderToSend(new Order(Order::TYPE::PROFIL, sizeof(allyBuff), &allyBuff));
            }
        }
    }
}

void Creature::sendBuff() const {
    auto it = _buffs.back();
    buffInfo buff;
    buff.targetId = _id;
    buff.type = (*it).getType();
    for (auto it = Server::getSingleton().getUsers().begin(); it != Server::getSingleton().getUsers().end() ; ++it) {
        if ((*it)->isConnected()){
            (*it)->stockOrderToSend(new Order(Order::TYPE::APPLY_BUFF, sizeof(buffInfo), &buff));
        }
    }
}

bool Creature::collideCreature(std::list<Creature*> const &list, Creature *me) {
    for (auto it = list.begin(); it != list.end() ; ++it) {
        if (!me->isDead() && !(*it)->isDead() && me != (*it)) {
            if (((*it)->_position - _position).normalise() < (_collideRange + (*it)->_collideRange) * 0.9) {
                return true;
            }
        }
    }
    return false;
}

bool Creature::collideWall(std::list<Wall*> const &list) {
    for (auto it = list.begin(); it != list.end() ; ++it) {
        if ((*it)->getMinCollide().x < _position.x && (*it)->getMaxCollide().x > _position.x
            && (*it)->getMinCollide().z < _position.z && (*it)->getMaxCollide().z > _position.z)
            return true;
    }
    return false;
}

void Creature::update(float timeSinceLastWork, std::pair<std::list<Creature *>, std::list<Wall *>> const &list) {
    Ogre::Vector3 vec;
    bool secu = false;

    if (!_dead) {
        if (collideWall(list.second))
            secu = true;
        vec = _position;
        _position += _moveVector * getSpeed() * timeSinceLastWork;
        if (!secu && _target && collideCreature(list.first, this)) {
            _position = vec;
            _moveTo = _position;
            _distanceTo = 0.0f;
            std::cout << "Colide Creature" << std::endl;
            changeDirection(Ogre::Vector3::ZERO);
        }
        else if (!secu && collideWall(list.second)) {
            _position = vec;
            _position.x += ((_moveVector.x > 0) ? 1 : -1) * getSpeed() * timeSinceLastWork;
            if (collideWall(list.second)){
                _position = vec;
                _position.z += ((_moveVector.z > 0) ? 1 : -1) * getSpeed() * timeSinceLastWork;
                if (collideWall(list.second)){
                    _position = vec;
                    _moveTo = _position;
                    changeDirection(Ogre::Vector3::ZERO);
                }
                else {
                    _moveVector.z = (_moveVector.z > 0) ? 1 : -1;
                    _moveVector.x = 0.0f;
                    sendPosition();
                }
            }
            else {
                _moveVector.x = (_moveVector.x > 0) ? 1 : -1;
                _moveVector.z = 0.0f;
                sendPosition();
            }
        }
        else {
            Ogre::Vector3 vectorDirection((_moveTo - _position).normalisedCopy());
            vec = _position;
            _position += vectorDirection * getSpeed() * timeSinceLastWork;
            if (_moveVector != vectorDirection && !collideWall(list.second)){
                _moveVector = (_moveTo - _position).normalisedCopy();
            }
            _position = vec;
            _distanceTo = (_moveTo - _position).normalise();
            if (_distanceTo < 5 && _moveVector != Ogre::Vector3::ZERO) {
                _position = _moveTo;
                changeDirection(Ogre::Vector3::ZERO);
            }
        }
    }

    for (auto it = _skills.begin(); it != _skills.end(); ++it) {
        (*it)->update(timeSinceLastWork);
    }
    for (auto it = _buffs.begin(); it != _buffs.end(); ++it){
        (*it)->update(timeSinceLastWork);
    }
    for (auto it = _buffs.begin(); it != _buffs.end(); ++it){
        if ((*it)->isDead()){
            Buff *tmp = (*it);
            delete tmp;
            _buffs.remove(*it);
            it = _buffs.begin();
        }
    }
    _regenTime += timeSinceLastWork;
    if (_regenTime >= 5.0)
    {
        regenMana(_spirit);
        _regenTime -= 5.0;
    }
}

void Creature::ai(float timeSinceLastUpdate, std::vector<Creature*> const &list){
    Creature *target = NULL;
    if (_target && _target->isDead()) {
        _target = NULL;
    }
    float actualDistance = 1000;
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (!(*it)->isDead() && ((*it)->getPosition() - _position).normalise() < actualDistance){
            target = (*it);
            actualDistance = ((*it)->getPosition() - _position).normalise();
        }
    }
    if (_target != target && target && (target->getPosition() - _position).normalise() < 1000) {
        _target = target;
        moveTo(target->getPosition());
    }
    else if (_target) {
        if (_lastMove > 0.5) {
            _moveTo = _target->getPosition();
            _moveVector = (_moveTo - _position).normalisedCopy();
            _distanceTo = (_moveTo - _position).normalise();
            _lastMove = 0.0f;
        }
    }
    _lastMove += timeSinceLastUpdate;
    if (_target)
        useSkill(NULL, (*_skills.begin())->getType(), _target);
}

bool Creature::isEnnemy() const{
    return _isEnnemy;
}

void Creature::setAlly() {
    _isEnnemy = false;
}