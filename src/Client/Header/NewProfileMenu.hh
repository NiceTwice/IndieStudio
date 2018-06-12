//
// Created by debruy_p on 07/05/16.
//

#ifndef TESTCEGUI_NEWPROFILEMENU_HH
#define TESTCEGUI_NEWPROFILEMENU_HH


#include "GuiMenu.hpp"

class NewProfileMenu : public GuiMenu {
protected:
    CEGUI::Window *text;
    CEGUI::Window *nameEditBox;
    CEGUI::Window *createButton;
    CEGUI::Window *backButton;
public:
    NewProfileMenu();
    virtual ~NewProfileMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();

private:
    bool back();
    bool create();
};


#endif //TESTCEGUI_NEWPROFILEMENU_HH
