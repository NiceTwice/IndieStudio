//
// Created by debruy_p on 11/05/16.
//

#include "GameMenu.hh"
#include "TutorialApplication.h"


std::string             getParticleSystemNextName(void){
    static size_t    id = 0;
    std::stringstream   ss;

    ss << "PS";
    ss << id;
    id++;
    return (ss.str());
}

GameMenu::GameMenu(): GuiMenu("GameMenu") {

}

GameMenu::~GameMenu() {

}

bool GameMenu::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    return (TutorialApplication::getSingleton().getViewManager()->getView()->frameRenderingQueued(evt));
}

void GameMenu::keyPressed(const OIS::KeyEvent &arg) {
    TutorialApplication::getSingleton().getViewManager()->getView()->keyPressed(arg);
    if (arg.key == OIS::KC_ESCAPE)
    {
        TutorialApplication::getSingleton().getServer()->deconnect();
        TutorialApplication::getSingleton().deconnectServer();
        TutorialApplication::getSingleton().getViewManager()->goToMenu();
        TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
    }
}

void GameMenu::keyReleased(const OIS::KeyEvent &arg) {
    TutorialApplication::getSingleton().getViewManager()->getView()->keyReleased(arg);
}

void GameMenu::mouseMoved(const OIS::MouseEvent &arg) {
    TutorialApplication::getSingleton().getViewManager()->getView()->mouseMoved(arg);
}

void GameMenu::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    TutorialApplication::getSingleton().getViewManager()->getView()->mousePressed(arg, id);
}
void GameMenu::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    TutorialApplication::getSingleton().getViewManager()->getView()->mouseReleased(arg, id);
}

void GameMenu::onDisplay() {
}

void GameMenu::onUnDisplay() {

}