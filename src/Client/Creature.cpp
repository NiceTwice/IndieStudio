//
// Created by nicetwice on 08/05/16.
//

#include "Creature.h"
#include "SoundManager.hh"

IND::Creature::Creature(const Ogre::Vector3 &position, IND::Entity::EntityType type, Ogre::SceneManager *sceneManager, size_t id) {
    sceneId = id;
    this->position = position;
    this->correctionPosition = position;
    this->_type = type;
    this->_scnMgr = sceneManager;
    this->mNode = sceneManager->getRootSceneNode()->createChildSceneNode(position);
    this->mNode->setPosition(position);
    this->_isMooving = false;
    this->_moveTo = position;
    this->_isDead = false;
    this->_target = NULL;
    this->_mDirection = Ogre::Vector3::ZERO;
    this->correctionSpeed = 1.0;
    this->_deathTimer = 5.0f;
}

IND::Creature::~Creature() {
}

void IND::Creature::setTarget(Creature *cr) {
    this->_target = cr;
}

void IND::Creature::setMoveTo(const Ogre::Vector3 &dest) {
    this->_moveTo = dest;
    _moveTo.y = 0;
}

void IND::Creature::setMoveTo(float x, float y, float z) {
    _moveTo.x = x;
    _moveTo.y = 0;
    _moveTo.z = z;
}

void IND::Creature::setChaseTarget(bool b) {
    this->_chaseTarget = b;
}

bool IND::Creature::isMooving(void) {
    return _isMooving;
}

size_t IND::Creature::getHp(void) const {
    return _hp;
}

size_t IND::Creature::getMaxHp(void) const {
    return _maxHp;
}

size_t IND::Creature::getMp(void) const {
    return _mp;
}

size_t IND::Creature::getMaxMp(void) const {
    return _maxMp;
}

void IND::Creature::setAnimationState(Ogre::AnimationState *state) {
    if (currentAnimation)
        currentAnimation->setEnabled(false);
    currentAnimation = state;
    currentAnimation->setEnabled(true);
}

void IND::Creature::useSpell(size_t  spellType, Creature *target) {
    std::vector<Spell*>::iterator           it = _spells.begin();
    while (it != _spells.end()){
        if ((*it)->getType() == spellType) {
            (*it)->use(target);
            break;
        }
        it++;
    }
}

void IND::Creature::learnSpell(Spell *spell) {
    _spells.push_back(spell);
}

void IND::Creature::dead(void) {
  SoundManager &sm = SoundManager::getSingleton();
  sm.playSound("death");
    currentAnimation->setEnabled(false);
    currentAnimation = mEntity->getAnimationState("Death");
    currentAnimation->setLoop(false);
    currentAnimation->setEnabled(true);
    currentAnimation->setTimePosition(0.0);
    _isDead = true;
}

bool IND::Creature::isDead(void) const {
    return (_isDead);
}

float IND::Creature::getWalkSpeed(void) const {
    return _mWalkSpeed;
}

float IND::Creature::getBasicWalkSpeed(void) const {
    return _basicWalkSpeed;
}

void IND::Creature::setWalkSpeed(float speed) {
    _mWalkSpeed = speed;
}

void IND::Creature::update(const Ogre::FrameEvent &evt) {
    std::vector<Spell*>::iterator   it = _spells.begin();
    while (it != _spells.end()){
        (*it)->update(evt);
        it++;
    }
    std::list<IND::Buff*>::iterator   itr = _buffs.begin();
    while (itr != _buffs.end()){
        if ((*itr)->isEnded()){
            _buffs.erase(itr);
            itr = _buffs.begin();
        }
        else {
            (*itr)->update(evt);
            itr++;
        }
    }
}

void IND::Creature::addBuff(Buff *buff) {
    buff->setTarget(this);
    _buffs.push_back(buff);
}

size_t IND::Creature::getSceneId(void) const {
    return sceneId;
}

IND::Spell *IND::Creature::getSpellByNumber(size_t nb) const {
    if ( nb < _spells.size() && _spells[nb] != NULL){
        return _spells[nb];
    }
    return NULL;
}

void IND::Creature::setDirection(const Ogre::Vector3 &dir) {
    _mDirection = dir;
}

void IND::Creature::setPosition(Ogre::Vector3 const &position) {
    if (_mDirection.x == 0 && _mDirection.y == 0) {
        mNode->setPosition(position);
        correctionPosition = position;
        correctionSpeed = 1.0;
    }
    float       distServer = (position - correctionPosition).normalise();
    float       distClient = (mNode->getPosition() - correctionPosition).normalise();

    if (distServer != 0 && distClient != 0) {
        correctionSpeed = distServer / distClient;
        if (correctionSpeed < 0.8)
            correctionSpeed = 0.8;
        else if (correctionSpeed > 1.2)
            correctionSpeed = 1.2;
    }
//    mNode->setPosition(position);
}

void IND::Creature::treatPositionAndDirection(Ogre::Vector3 const &dir, Ogre::Vector3 const &position) {
    if (_mDirection.x != dir.x || _mDirection.y == dir.z) {
        _mDirection = dir;
        mNode->setPosition(position);
        correctionPosition = position;
        correctionSpeed = 1.0;
    }
    float       distServer = (position - correctionPosition).normalise();
    float       distClient = (mNode->getPosition() - correctionPosition).normalise();

    if (distServer != 0 && distClient != 0) {
        correctionSpeed = distServer / distClient;
        if (correctionSpeed < 0.8)
            correctionSpeed = 0.8;
        else if (correctionSpeed > 1.2)
            correctionSpeed = 1.2;
    }
}

void IND::Creature::setCurrentMp(size_t value) {
    std::stringstream   ss;

    _mp = value;
    ss << _mp << "/" << _maxMp;
    currentMpstr = ss.str();
}

void IND::Creature::setCurrentHp(size_t value) {
    std::stringstream   ss;

    _hp = value;
    ss << _hp << "/" << _maxHp;
    currentHpStr = ss.str();
}

void IND::Creature::setMaxHp(size_t const value) {
    std::stringstream   ss;

    _maxHp = value;
    ss <<  _hp<< "/" << _maxHp;
    currentHpStr = ss.str();
}

void IND::Creature::setMaxMp(size_t const value) {
    std::stringstream   ss;

    _maxMp = value;
    ss <<  _mp << "/" << _maxMp;
    currentMpstr = ss.str();
}

std::string const &IND::Creature::getCurrentHpStr() const {
    return currentHpStr;
}

std::string const &IND::Creature::getCurrentMpStr() const {
    return currentMpstr;
}

float IND::Creature::getDeathTimer() const {
    return _deathTimer;
}

void IND::Creature::respawnIt(const Ogre::Vector3 &position) {
    _isDead = false;
    this->position = position;
    this->correctionPosition = position;
    this->correctionSpeed = 1.0;
    this->_mDirection = Ogre::Vector3::ZERO;
    setCurrentHp(this->_maxHp);
    setCurrentMp(this->_maxMp);
    _isMooving = false;
    resetAnimation();
}








































































