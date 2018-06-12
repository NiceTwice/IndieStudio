//
// Created by debruy_p on 24/05/16.
//

#include "MenuView.hh"
#include "TutorialApplication.h"
#include "Golem.h"
#include "ObjectFactory.hpp"

MenuView::MenuView() {

}

MenuView::~MenuView() {

}

bool MenuView::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    for (auto j = creatures.begin(); j != creatures.end(); ++j) {
        (*j)->update(evt);
    }
    for (auto k = entitys.begin(); k != entitys.end() ; ++k) {
        (*k)->getAnimationState("Stand")->addTime(evt.timeSinceLastFrame);
    }
  return false;
}

void MenuView::keyPressed(const OIS::KeyEvent &arg) {

}

void MenuView::keyReleased(const OIS::KeyEvent &arg) {

}

void MenuView::mouseMoved(const OIS::MouseEvent &arg) {

}

void MenuView::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {

}

void MenuView::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {

}

void MenuView::onCreate() {
    mSceneMgr = TutorialApplication::getSingleton().getRoot()->createSceneManager(Ogre::ST_GENERIC);
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    //mCamera->setPosition(Ogre::Vector3(0,1000,600));
    mCamera->setPosition(Ogre::Vector3(500,500,350));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,50,75));
    mCamera->setNearClipDistance(10);
    // Create one viewport, entire window
    Ogre::Viewport* vp = TutorialApplication::getSingleton().getWindow()->addViewport(mCamera);
//    vp->setBackgroundColour(Ogre::ColourValue(255,255,255));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
            "ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            20000, 20000, 40, 40,
            true,
            1, 120, 120,
            Ogre::Vector3::UNIT_Z);
    Ogre::Entity *groundEntity = mSceneMgr->createEntity("ground", "ground");
    groundEntity->setMaterialName("Examples/Rockwall");
    mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -0.02, 0))->attachObject(groundEntity);


    creatures.push_back(IND::ObjectFactory::createCreature(4, Ogre::Vector3(100, 0, -300), IND::Entity::Ally, mSceneMgr, 1));
    creatures[0]->getEntity()->getAnimationState("EmoteDance")->setEnabled(true);
    creatures[0]->getEntity()->getAnimationState("EmoteDance")->setLoop(true);
    creatures[0]->setAnimationState(creatures[0]->getEntity()->getAnimationState("EmoteDance"));

    addEntity("trollBand.mesh", Ogre::Vector3(-100, 0, 300), Ogre::Vector3(70, 70, 70));
    addEntity("taurenBand.mesh", Ogre::Vector3(-50, 0, -100), Ogre::Vector3(70, 70, 70));
    addEntity("orcBand.mesh", Ogre::Vector3(50, 0, 130), Ogre::Vector3(70, 70, 70));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    Ogre::Light *spotLight = mSceneMgr->createLight("SpotLight1");
    spotLight->setDiffuseColour(0, 0, 1);
    spotLight->setSpecularColour(0, 0, 1);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDirection(Ogre::Vector3(0, -1, 0));
    spotLight->setPosition(0, 500, -300);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    spotLight = mSceneMgr->createLight("SpotLight2");
    spotLight->setDiffuseColour(1, 0, 0);
    spotLight->setSpecularColour(1, 0, 0);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDirection(Ogre::Vector3(0, -1, 0));
    spotLight->setPosition(0, 500, -100);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    spotLight = mSceneMgr->createLight("SpotLight3");
    spotLight->setDiffuseColour(0, 1, 0);
    spotLight->setSpecularColour(0, 1, 0);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDirection(Ogre::Vector3(0, -1, 0));
    spotLight->setPosition(0, 500, 100);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
}

void MenuView::addEntity(std::string const &meshName, Ogre::Vector3 const &pos, Ogre::Vector3 const &scale){
    entitys.push_back(mSceneMgr->createEntity(meshName));
    Ogre::SceneNode         *tmp;
    tmp  = mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
    tmp->attachObject(entitys[entitys.size() - 1]);
    tmp->setScale(scale);
    entitys[entitys.size() - 1]->getAnimationState("Stand")->setEnabled(true);
    entitys[entitys.size() - 1]->getAnimationState("Stand")->setLoop(true);

}

void MenuView::onDestroy() {
    TutorialApplication::getSingleton().getWindow()->removeViewport(0);
}
