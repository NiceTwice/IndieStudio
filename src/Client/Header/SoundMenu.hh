//
// Created by debruy_p on 26/05/16.
//

#ifndef TESTCEGUI_SOUNDMENU_HH
#define TESTCEGUI_SOUNDMENU_HH


#include <CEGUI/Window.h>
#include "GuiMenu.hpp"

class SoundMenu : public GuiMenu {
protected:
    CEGUI::Window *masterVolumeText;
    CEGUI::Window *masterVolume;
    CEGUI::Window *musicVolumeText;
    CEGUI::Window *musicVolume;
    CEGUI::Window *effectsVolumeText;
    CEGUI::Window *effectsVolume;
    CEGUI::Window *backButton;
public:
    SoundMenu();
    virtual ~SoundMenu();

    void keyPressed(const OIS::KeyEvent &arg);
    void onDisplay();

private:
    bool master();
    bool music();
    bool effects();
    bool back();
};


#endif //TESTCEGUI_SOUNDMENU_HH
