//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_MAINMENU_HH
#define TESTCEGUI_MAINMENU_HH

#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <OIS/OIS.h>
#include <SdkCameraMan.h>
#include "GuiMenu.hpp"

class MainMenu : public GuiMenu{
protected:
    CEGUI::Window *_createGameButton;
    CEGUI::Window *_joinGameButton;
    CEGUI::Window *_optionsButton;
    CEGUI::Window *_profileButton;
    CEGUI::Window *_quitButton;
    CEGUI::Window *_text;

public:
    MainMenu();
    virtual ~MainMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();
    void onUnDisplay();

private:
    bool createGame();
    bool joinGame();
    bool options();
    bool profile();
    bool quit();
};


#endif //TESTCEGUI_MAINMENU_HH
