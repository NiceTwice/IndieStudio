//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_PROFILEMENU_HH
#define TESTCEGUI_PROFILEMENU_HH


#include <OIS.h>
#include "GuiMenu.hpp"

class ProfileMenu : public GuiMenu {
protected:
    CEGUI::Window *profileBack;
    CEGUI::Listbox *objectComboBox;
    CEGUI::Window *currProfilName;
    CEGUI::Window *newProfile;
    CEGUI::Window *editProfile;
    CEGUI::Window *deleteProfile;
    CEGUI::Window *errortext;
    CEGUI::Window *backButton;
public:
    ProfileMenu();
    virtual ~ProfileMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();
    void onUnDisplay();

private:
    bool back();
    bool ne();
    bool edit();
    bool del();

    bool onSelectionChanged(const CEGUI::EventArgs &e);

};


#endif //TESTCEGUI_PROFILEMENU_HH
