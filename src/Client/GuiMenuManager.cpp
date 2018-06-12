//
// Created by debruy_p on 06/05/16.
//

#include <iostream>
#include "GuiMenuManager.hh"

GuiMenuManager::GuiMenuManager():_menus(), _currentMenu(NULL) {
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");

    CEGUI::Window *sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

GuiMenuManager::~GuiMenuManager() {
    for (auto it = _menus.begin(); it != _menus.end(); ++it) {
        delete *it;
    }
    _menus.clear();
}

void GuiMenuManager::addMenu(GuiMenu *menu) {
    _menus.push_back(menu);
}

GuiMenu *GuiMenuManager::getMenu(std::string const &name) const {
    for (auto it = _menus.begin(); it != _menus.end(); ++it) {
        if ((*it)->getRoot()->getName().compare(name) == 0) {
            return (*it);
        }
    }
    std::cerr << "Error: Menu " << name << " dosen't exist!" << std::endl;
    return NULL;
}

void GuiMenuManager::goToMenu(GuiMenu *menu) {
    if (menu) {
        if (_currentMenu) {
            CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(_currentMenu->getRoot());
            _currentMenu->onUnDisplay();
        }
        _currentMenu = menu;
        _currentMenu->onDisplay();
        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(menu->getRoot());
    }
}

void GuiMenuManager::goToMenu(std::string const &name) {
    goToMenu(getMenu(name));
}

GuiMenu *GuiMenuManager::getCurrentMenu() const {
    return _currentMenu;
}