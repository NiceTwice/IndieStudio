//
// Created by debruy_p on 07/05/16.
//

#ifndef TESTCEGUI_EDITPROFILEMENU_HH
#define TESTCEGUI_EDITPROFILEMENU_HH


#include "GuiMenu.hpp"

class EditProfileMenu  : public GuiMenu {
protected:
    CEGUI::Window *text;
    CEGUI::Window *nameEditBox;
    CEGUI::Window *createButton;
    CEGUI::Window *backButton;
public:
    EditProfileMenu();
    virtual ~EditProfileMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();

private:
    bool back();
    bool save();
};

#endif //TESTCEGUI_EDITPROFILEMENU_HH
