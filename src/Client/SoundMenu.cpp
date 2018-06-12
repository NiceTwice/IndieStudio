//
// Created by debruy_p on 26/05/16.
//

#include "SoundMenu.hh"
#include "LanguageManager.hh"
#include "TutorialApplication.h"
#include "SoundManager.hh"

SoundMenu::SoundMenu(): GuiMenu("SoundMenu"){

    //
    /// Master Volume
    //

    masterVolumeText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "SoundMenu/masterVolumeText");
    masterVolumeText->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    masterVolumeText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.25, 0)));
    _root->addChild(masterVolumeText);

    masterVolume = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Slider", "SoundMenu/masterVolume");
    masterVolume->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    masterVolume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.30, 0)));
    static_cast<CEGUI::Slider *>(masterVolume)->setMaxValue(1.0f);
    static_cast<CEGUI::Slider *>(masterVolume)->setCurrentValue(SoundManager::getSingleton().getGeneralVolume());
    masterVolume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundMenu::master, this));
    _root->addChild(masterVolume);

    //
    /// Music Volume
    //

    musicVolumeText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "SoundMenu/musicVolumeText");
    musicVolumeText->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    musicVolumeText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.40, 0)));
    _root->addChild(musicVolumeText);

    musicVolume = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Slider", "SoundMenu/musicVolume");
    musicVolume->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    musicVolume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.45, 0)));
    static_cast<CEGUI::Slider *>(musicVolume)->setMaxValue(1.0f);
    static_cast<CEGUI::Slider *>(musicVolume)->setCurrentValue(SoundManager::getSingleton().getAmbianceVolume());
    musicVolume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundMenu::music, this));
    _root->addChild(musicVolume);

    //
    /// Effects Volume
    //

    effectsVolumeText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "SoundMenu/effectsVolumeText");
    effectsVolumeText->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    effectsVolumeText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.55, 0)));
    effectsVolumeText->setVisible(false);
    _root->addChild(effectsVolumeText);

    effectsVolume = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Slider", "SoundMenu/effectsVolume");
    effectsVolume->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    effectsVolume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.60, 0)));
    static_cast<CEGUI::Slider *>(effectsVolume)->setMaxValue(1.0f);
    static_cast<CEGUI::Slider *>(effectsVolume)->setCurrentValue(SoundManager::getSingleton().getEffectVolume());
    effectsVolume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundMenu::effects, this));
    effectsVolume->setVisible(false);
    _root->addChild(effectsVolume);
    //
    /// Button Back
    //

    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "SoundMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.70, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SoundMenu::back, this));
    _root->addChild(backButton);
}

SoundMenu::~SoundMenu() {

}

void SoundMenu::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
    {
        back();
    }
}

void SoundMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    masterVolumeText->setText(lang->getString("MasterVolume"));
    musicVolumeText->setText(lang->getString("MusicVolume"));
    effectsVolumeText->setText(lang->getString("EffectsVolume"));
    backButton->setText(lang->getString("Back"));
}

bool SoundMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
}

bool SoundMenu::effects() {
    SoundManager::getSingleton().setEffectVolume(static_cast<CEGUI::Slider *>(effectsVolume)->getCurrentValue());
    SoundManager::getSingleton().playSound("FireBall");
    return false;
}

bool SoundMenu::master() {
    SoundManager::getSingleton().setGeneralVolume(static_cast<CEGUI::Slider *>(masterVolume)->getCurrentValue());
    return false;
}

bool SoundMenu::music() {
    SoundManager::getSingleton().setAmbianceVolume(static_cast<CEGUI::Slider *>(musicVolume)->getCurrentValue());
    return false;
}





