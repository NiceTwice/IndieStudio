//
// Created by debruy_p on 05/05/16.
//

/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/


#include <OGRE/OgreException.h>
#include "TutorialApplication.h"
#include "MainMenu.hh"
#include "OptionsMenu.hh"
#include "JoinGameMenu.hh"
#include "ProfileMenu.hh"
#include "NewProfileMenu.hh"
#include "EditProfileMenu.hh"
#include "LanguageMenu.hh"
#include "SaloonMenu.hh"
#include "GameMenu.hh"
#include "SoundMenu.hh"

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
        case OIS::MB_Left:
            return CEGUI::LeftButton;

        case OIS::MB_Right:
            return CEGUI::RightButton;

        case OIS::MB_Middle:
            return CEGUI::MiddleButton;

        default:
            return CEGUI::LeftButton;
    }
}

TutorialApplication TutorialApplication::m_instance=TutorialApplication();

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void): BaseApplication(), _server(NULL)
{

}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
    delete _guiMenuManager;
    delete _profileManager;
    delete _languageManager;
    delete _viewManager;
}
//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    _viewManager = new ViewManager();

    _languageManager = new LanguageManager();
    _languageManager->generateLanguageFile("Test");

    _profileManager = new ProfileManager();

    _guiMenuManager = new GuiMenuManager();
    _guiMenuManager->addMenu(new MainMenu());
    _guiMenuManager->addMenu(new OptionsMenu());
    _guiMenuManager->addMenu(new LanguageMenu());
    _guiMenuManager->addMenu(new JoinGameMenu());
    _guiMenuManager->addMenu(new ProfileMenu());
    _guiMenuManager->addMenu(new NewProfileMenu());
    _guiMenuManager->addMenu(new EditProfileMenu());
    _guiMenuManager->addMenu(new SoundMenu());
    _guiMenuManager->addMenu(new SaloonMenu());
    _guiMenuManager->addMenu(new GameMenu());
    _guiMenuManager->goToMenu("MainMenu");

}

TutorialApplication &TutorialApplication::getSingleton() {
    return m_instance;
}

GuiMenuManager *TutorialApplication::getGuiMenuManager() const {
    return _guiMenuManager;
}

void TutorialApplication::stop() {
    mShutDown = true;
}

bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg )
{
    std::cout.precision(17);
    _guiMenuManager->getCurrentMenu()->keyPressed(arg);
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);
    return true;
}

bool TutorialApplication::keyReleased( const OIS::KeyEvent &arg )
{
    _guiMenuManager->getCurrentMenu()->keyReleased(arg);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
    return true;
}

bool TutorialApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    _guiMenuManager->getCurrentMenu()->mouseMoved(arg);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel)
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    return true;
}

bool TutorialApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    _guiMenuManager->getCurrentMenu()->mousePressed(arg, id);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    return true;
}

bool TutorialApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    _guiMenuManager->getCurrentMenu()->mouseReleased(arg, id);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    return true;
}

ProfileManager *TutorialApplication::getProfileManager() const {
    return _profileManager;
}

LanguageManager *TutorialApplication::getLanguageManager() const {
    return _languageManager;
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    _guiMenuManager->getCurrentMenu()->frameRenderingQueued(evt);
    _viewManager->change();
    _viewManager->updateMenu(evt);
    return true;
}

void TutorialApplication::setServer(Server *server) {
    _server = server;
}

void TutorialApplication::deconnectServer() {
    if (_server) {
        delete _server;
        _server = NULL;
    }
}

Server *TutorialApplication::getServer() const {
    return _server;
}

std::chrono::time_point<std::chrono::high_resolution_clock> const TutorialApplication::getTimeMillis(void) const{
    return std::chrono::high_resolution_clock::now();
}

Ogre::Root *TutorialApplication::getRoot() {
    return mRoot;
}

Ogre::RenderWindow *TutorialApplication::getWindow() {
    return mWindow;
}

ViewManager *TutorialApplication::getViewManager() const {
    return _viewManager;
}
