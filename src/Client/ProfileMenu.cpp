//
// Created by debruy_p on 06/05/16.
//

#include "ProfileMenu.hh"
#include "TutorialApplication.h"
#include "Readdir.hh"


ProfileMenu::ProfileMenu():GuiMenu("ProfileMenu") {


  //
    /// Profile Background
    //

    profileBack = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticImage", "ProfileMenu/CurrentProfileBackground");
    profileBack->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.30, 0)));
    profileBack->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.30, 0)));
    _root->addChild(profileBack);

    //
    /// Current Profile Name
    //

    currProfilName = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Label", "ProfileMenu/CurrentProfileName");
    currProfilName->setSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(0.1, 0)));
    currProfilName->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0, 0), CEGUI::UDim(0.1, 0)));
    profileBack->addChild(currProfilName);

    //
    /// Error text
    //

    errortext = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "EditProfileMenu/Text");
    errortext->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    errortext->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.60, 0)));
    _root->addChild(errortext);

    //
    /// Button New Profile
    //

    newProfile = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "ProfileMenu/NewProfileButton");
    newProfile->setSize(CEGUI::USize(CEGUI::UDim(0.12, 0), CEGUI::UDim(0.05, 0)));
    newProfile->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.65, 0)));
    newProfile->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ProfileMenu::ne, this));
    _root->addChild(newProfile);

    //
    /// Button Edit Profile
    //

    editProfile = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "ProfileMenu/EditProfileButton");
    editProfile->setSize(CEGUI::USize(CEGUI::UDim(0.12, 0), CEGUI::UDim(0.05, 0)));
    editProfile->setPosition(CEGUI::UVector2(CEGUI::UDim(0.44, 0), CEGUI::UDim(0.65, 0)));
    editProfile->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ProfileMenu::edit, this));
    _root->addChild(editProfile);

    //
    /// Button Delete Profile
    //

    deleteProfile = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "ProfileMenu/DeleteProfileButton");
    deleteProfile->setSize(CEGUI::USize(CEGUI::UDim(0.12, 0), CEGUI::UDim(0.05, 0)));
    deleteProfile->setPosition(CEGUI::UVector2(CEGUI::UDim(0.58, 0), CEGUI::UDim(0.65, 0)));
    deleteProfile->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ProfileMenu::del, this));
    _root->addChild(deleteProfile);

    //
    /// Button Back
    //

    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "ProfileMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.75, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ProfileMenu::back, this));
    _root->addChild(backButton);
}

ProfileMenu::~ProfileMenu() {

}

void ProfileMenu::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
    {
        back();
    }
}

bool ProfileMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
    return false;
}

bool ProfileMenu::onSelectionChanged(const CEGUI::EventArgs &e)
{
    if (objectComboBox->getFirstSelectedItem()) {
        std::string file(objectComboBox->getFirstSelectedItem()->getText().c_str());
        file += ".profile";
        if (TutorialApplication::getSingleton().getProfileManager()->loadProfile(file)) {
            errortext->setText("");
            TutorialApplication::getSingleton().getProfileManager()->saveProfile();
        }
        else {
            errortext->setText(TutorialApplication::getSingleton().getLanguageManager()->getString("ProfileError"));
        }
        currProfilName->setText(TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile()->getName());


        LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

        newProfile->setText(lang->getString("New"));
        editProfile->setText(lang->getString("Edit"));
        deleteProfile->setText(lang->getString("Delete"));
        backButton->setText(lang->getString("Back"));
    }
    return true;
}

bool ProfileMenu::ne() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("NewProfileMenu");
    return false;
}

void ProfileMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    newProfile->setText(lang->getString("New"));
    editProfile->setText(lang->getString("Edit"));
    deleteProfile->setText(lang->getString("Delete"));
    errortext->setText("");
    backButton->setText(lang->getString("Back"));


    if (TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile())
        currProfilName->setText(TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile()->getName());
    else
        currProfilName->setText("Anonymous");

    objectComboBox = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Listbox", "ProfileMenu/CurrentProfileName"));
    objectComboBox->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.30, 0)));
    objectComboBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.30, 0)));


    objectComboBox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&ProfileMenu::onSelectionChanged, this));

    _root->addChild(objectComboBox);

    CEGUI::ListboxTextItem *itemCombobox;
    std::ifstream in;
    std::string dir(PROFILE_DIRECTORY);
    int magic = 0;
    std::vector<std::string> files = Readdir::getAllFile(PROFILE_DIRECTORY);
    int i = 0;
    for (auto it = files.begin(); it != files.end(); ++it) {
        try {
            if ((*it).compare("current") != 0) {
                in.open(dir + "/" + (*it));
                in >> magic;
                if (magic == PROFILE_MAGICNBR) {
                    itemCombobox = new CEGUI::ListboxTextItem((*it).substr(0, (*it).find(".profile")), i);
                    objectComboBox->addItem(itemCombobox);
                }
                else {
                    std::cerr << "LoadProfile: " << (*it) << ": Bad magic nbr" << std::endl;
                }
                in.close();
                i++;
            }
        }
        catch (std::exception e) {
            std::cerr << "Open .profile file: " << e.what() << std::endl;
        }
    }
}

void ProfileMenu::onUnDisplay() {
    objectComboBox->destroy();
}

bool ProfileMenu::del() {
    ProfileManager *manager = TutorialApplication::getSingleton().getProfileManager();
    manager->removeProfile();
    onUnDisplay();
    onDisplay();
    return false;
}

bool ProfileMenu::edit() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("EditProfileMenu");
    return false;
}









