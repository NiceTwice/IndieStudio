//
// Created by debruy_p on 08/05/16.
//

#ifndef TESTCEGUI_LANGUAGEMENU_HH
#define TESTCEGUI_LANGUAGEMENU_HH


#include <OIS.h>
#include "GuiMenu.hpp"

class LanguageMenu : public GuiMenu {
protected:
    CEGUI::Listbox *objectComboBox;
    CEGUI::Window *text;
    CEGUI::Window *backButton;

public:
    LanguageMenu();
    virtual ~LanguageMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();
    void onUnDisplay();

private:
    bool onSelectionChanged(const CEGUI::EventArgs &e);

    bool back();
};


#endif //TESTCEGUI_LANGUAGEMENU_HH
