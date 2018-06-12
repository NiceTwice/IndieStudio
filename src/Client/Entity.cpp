//
// Created by nicetwice on 08/05/16.
//

#include "Entity.h"

IND::Entity::~Entity() {
}

Ogre::SceneNode *IND::Entity::getSceneNode(void) const{
    return this->mNode;
}

Ogre::Entity *IND::Entity::getEntity(void) const {
    return mEntity;
}

Ogre::SceneManager *IND::Entity::getSceneManager(void) const {
    return _scnMgr;
}



