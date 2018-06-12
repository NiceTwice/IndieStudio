//
// Created by debruy_p on 11/05/16.
//

#ifndef TESTCEGUI_GAMEMENU_HH
#define TESTCEGUI_GAMEMENU_HH


#include <OIS/OIS.h>
#include <OGRE/SdkCameraMan.h>
#include <OGRE/SdkTrays.h>
#include "GuiMenu.hpp"
#include "Creature.h"
#include "Order.hh"
#include "Thread.hpp"
#include "Spell.h"
#include "GameView.h"

class GameMenu : public GuiMenu{
public:
    GameMenu();
    virtual ~GameMenu();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    void keyPressed(const OIS::KeyEvent &arg);
    void keyReleased(const OIS::KeyEvent &arg );
    void mouseMoved(const OIS::MouseEvent &arg );
    void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void onDisplay();
    void onUnDisplay();
};

#endif //TESTCEGUI_GAMEMENU_HH
