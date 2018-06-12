//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_JOINGAMEMENU_HH
#define TESTCEGUI_JOINGAMEMENU_HH


#include "GuiMenu.hpp"

class JoinGameMenu : public GuiMenu {
protected:
    CEGUI::Window *ipStaticText;
    CEGUI::Window *ipEditBox;
    CEGUI::Window *portStaticText;
    CEGUI::Window *portEditBox;
    CEGUI::Window *mdpStaticText;
    CEGUI::Window *mdpEditBox;
    CEGUI::Window *errortext;
    CEGUI::Window *connectButton;
    CEGUI::Window *backButton;
public:
    JoinGameMenu();
    virtual ~JoinGameMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();

private:
    bool connect();
    bool back();
};


#endif //TESTCEGUI_JOINGAMEMENU_HH
