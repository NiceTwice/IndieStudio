//
// Created by nicetwice on 31/05/16.
//

#include "WallCube.h"

IND::WallCube::WallCube(Ogre::Vector3 const &position, Ogre::Vector3 const &rotation,
                        Ogre::SceneManager *sceneManager) {
    this->position = position;
    this->rotation = rotation;
    this->_scnMgr = sceneManager;
    this->_meshName = "wallCubic.mesh";
    mEntity = sceneManager->createEntity(_meshName);
    this->mNode = sceneManager->getRootSceneNode()->createChildSceneNode(position);
    this->mNode->setPosition(position);
    mNode->attachObject(mEntity);
    Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
    Ogre::Quaternion quat = src.getRotationTo(rotation);
    mNode->rotate(quat);
    mNode->scale(119, 70, 119);
}

IND::WallCube::~WallCube() {

}