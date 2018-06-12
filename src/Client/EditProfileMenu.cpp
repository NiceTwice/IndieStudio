//
// Created by debruy_p on 07/05/16.
//

#include "EditProfileMenu.hh"
#include "TutorialApplication.h"

EditProfileMenu::EditProfileMenu(): GuiMenu("EditProfileMenu") {

    //
    /// Text Enter Profile's name
    //

    text = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "EditProfileMenu/Text");
    text->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    text->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.35, 0)));
    _root->addChild(text);

    //
    /// EditBox Profile's name
    //

    nameEditBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Editbox", "EditProfileMenu/NameEditBox");
    nameEditBox->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    nameEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.40, 0)));
    _root->addChild(nameEditBox);

    //
    /// Button Save
    //

    createButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "EditProfileMenu/SaveButton");
    createButton->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.05, 0)));
    createButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.60, 0)));
    createButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditProfileMenu::save, this));
    _root->addChild(createButton);

    //
    /// Button Back
    //

    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "EditProfileMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.75, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&EditProfileMenu::back, this));
    _root->addChild(backButton);
}

EditProfileMenu::~EditProfileMenu() {

}

void EditProfileMenu::keyPressed(const OIS::KeyEvent &arg) {
    switch (arg.key){
        case (OIS::KC_ESCAPE):
            back();
            break;
        case (const OIS::KeyCode) (28): //ENTER
            save();
            break;
    }
}

void EditProfileMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    text->setText(lang->getString("EnterProfileName"));
    createButton->setText(lang->getString("Save"));
    backButton->setText(lang->getString("Back"));

    nameEditBox->setText(TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile()->getName());
    nameEditBox->activate();
}

bool EditProfileMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("ProfileMenu");
    return false;
}

bool EditProfileMenu::save() {
    ProfileManager *manager = TutorialApplication::getSingleton().getProfileManager();
    if (!nameEditBox->getText().empty()){
        manager->removeProfile();
        manager->newProfile(nameEditBox->getText().c_str());
        manager->saveProfile();
        TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("ProfileMenu");
    }
    return false;
}