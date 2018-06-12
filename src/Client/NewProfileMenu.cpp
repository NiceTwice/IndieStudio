//
// Created by debruy_p on 07/05/16.
//

#include "NewProfileMenu.hh"
#include "TutorialApplication.h"

NewProfileMenu::NewProfileMenu(): GuiMenu("NewProfileMenu") {

    //
    /// Text Enter Profile's name
    //

    text = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "NewProfileMenu/Text");
    text->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    text->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.35, 0)));
    _root->addChild(text);

    //
    /// EditBox Profile's name
    //

    nameEditBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Editbox", "NewProfileMenu/NameEditBox");
    nameEditBox->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    nameEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.40, 0)));
    _root->addChild(nameEditBox);

    //
    /// Button Create
    //

    createButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "NewProfileMenu/CreateButton");
    createButton->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.05, 0)));
    createButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.60, 0)));
    createButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&NewProfileMenu::create, this));
    _root->addChild(createButton);

    //
    /// Button Back
    //

    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "NewProfileMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.75, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&NewProfileMenu::back, this));
    _root->addChild(backButton);

}

NewProfileMenu::~NewProfileMenu() {

}

void NewProfileMenu::keyPressed(const OIS::KeyEvent &arg) {
    switch (arg.key){
        case (OIS::KC_ESCAPE):
            back();
            break;
        case (const OIS::KeyCode) (28): //ENTER
            create();
            break;
    }
}

bool NewProfileMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("ProfileMenu");
    return false;
}

void NewProfileMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    text->setText(lang->getString("EnterProfileName"));
    createButton->setText(lang->getString("Create"));
    backButton->setText(lang->getString("Back"));


    nameEditBox->setText("");
    //nameEditBox->setEnabled(true);
    nameEditBox->activate();
}

bool NewProfileMenu::create() {
    ProfileManager *manager = TutorialApplication::getSingleton().getProfileManager();
    if (!nameEditBox->getText().empty()) {
        std::string name(nameEditBox->getText().c_str());
        std::replace(name.begin(), name.end(), ' ', '_');
        manager->newProfile(name);
        back();
    }
    return false;
}

