//
// Created by debruy_p on 06/05/16.
//

#include "OptionsMenu.hh"
#include "TutorialApplication.h"

OptionsMenu::OptionsMenu():GuiMenu("OptionsMenu") {


    //
    /// Button Graphism
    //

    graphismButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "OptionsMenu/GraphismButton");
    graphismButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    graphismButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.30, 0)));
    graphismButton->setVisible(false);
    _root->addChild(graphismButton);

    //
    /// Button Sound
    //

    soundButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "OptionsMenu/SoundButton");
    soundButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    soundButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.40, 0)));
    soundButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionsMenu::sound, this));
    _root->addChild(soundButton);

    //
    /// Button Controls
    //

    controlsButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "OptionsMenu/ControlsButton");
    controlsButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    controlsButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.50, 0)));
    controlsButton->setVisible(false);
    _root->addChild(controlsButton);

    //
    /// Button Language
    //

    languageButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "OptionsMenu/LanguageButton");
    languageButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    languageButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.60, 0)));
    languageButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionsMenu::language, this));
    _root->addChild(languageButton);

    //
    /// Button Back
    //

    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "OptionsMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.70, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionsMenu::back, this));
    _root->addChild(backButton);
}

OptionsMenu::~OptionsMenu() {

}

void OptionsMenu::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
    {
        back();
    }
}

bool OptionsMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
    return false;
}

void OptionsMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    graphismButton->setText(lang->getString("Graphism"));
    soundButton->setText(lang->getString("Sound"));
    controlsButton->setText(lang->getString("Controls"));
    languageButton->setText(lang->getString("Language"));
    backButton->setText(lang->getString("Back"));
}

bool OptionsMenu::language() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("LanguageMenu");
    return false;
}

bool OptionsMenu::sound() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("SoundMenu");
}