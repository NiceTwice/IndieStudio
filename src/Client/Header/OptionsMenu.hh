//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_OPTIONSMENU_HH
#define TESTCEGUI_OPTIONSMENU_HH


#include "GuiMenu.hpp"

class OptionsMenu : public GuiMenu {
protected:
    CEGUI::Window *graphismButton;
    CEGUI::Window *soundButton;
    CEGUI::Window *controlsButton;
    CEGUI::Window *languageButton;
    CEGUI::Window *backButton;
public:
    OptionsMenu();
    virtual ~OptionsMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();

private:
    bool sound();
    bool language();
    bool back();
};


#endif //TESTCEGUI_OPTIONSMENU_HH
