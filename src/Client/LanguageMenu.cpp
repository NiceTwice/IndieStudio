//
// Created by debruy_p on 08/05/16.
//

#include "LanguageMenu.hh"
#include "TutorialApplication.h"
#include "Readdir.hh"

LanguageMenu::LanguageMenu(): GuiMenu("LanguageMenu") {

    //
    /// Error text
    //

    text = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "EditProfileMenu/Text");
    text->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    text->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.60, 0)));
    _root->addChild(text);

    //
    /// Button Back
    //

    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "OptionsMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.70, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LanguageMenu::back, this));
    _root->addChild(backButton);
}

LanguageMenu::~LanguageMenu() {

}

void LanguageMenu::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
    {
        back();
    }
}

void LanguageMenu::onDisplay() {

    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();
    backButton->setText(lang->getString("Back"));
    text->setText("");

    objectComboBox = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Listbox", "LanguageMenu/LanguageList"));
    objectComboBox->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.30, 0)));
    objectComboBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.30, 0)));

    objectComboBox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&LanguageMenu::onSelectionChanged, this));

    _root->addChild(objectComboBox);

    CEGUI::ListboxTextItem *itemCombobox;
    std::ifstream in;
    std::string dir(LANGUAGE_DIRECTORY);
    int magic = 0;
        std::vector<std::string> files = Readdir::getAllFile(LANGUAGE_DIRECTORY);
        int i = 0;
    for (auto it = files.begin(); it != files.end(); ++it) {
        try {
            in.open(dir + "/" + (*it));
            in >> magic;
            if (magic == LANGUAGE_MAGICNBR) {
                itemCombobox = new CEGUI::ListboxTextItem((*it).substr(0, (*it).find(".lang")), i);
                objectComboBox->addItem(itemCombobox);
            }
            else {
                std::cerr << "LoadLanguage: " << (*it) << ": Bad magic nbr" << std::endl;
            }
            in.close();
            i++;
        }
        catch (std::exception e) {
            std::cerr << "Open .lang file: " << e.what() << std::endl;
        }
    }
}

void LanguageMenu::onUnDisplay() {
    objectComboBox->destroy();
}

bool LanguageMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("OptionsMenu");

    return false;
}

bool LanguageMenu::onSelectionChanged(const CEGUI::EventArgs &e) {

    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    if (objectComboBox->getFirstSelectedItem()) {
        std::string file(objectComboBox->getFirstSelectedItem()->getText().c_str());
        file += ".lang";
        if (!lang->loadLanguage(file)) {
            text->setText(lang->getString("LanguageError"));
        }
        else {
            text->setText("");
            TutorialApplication::getSingleton().getProfileManager()->saveProfile();
        }
        backButton->setText(lang->getString("Back"));
    }
    return false;
}