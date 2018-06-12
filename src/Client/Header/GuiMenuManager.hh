//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_GUIMENUMANAGER_HH
#define TESTCEGUI_GUIMENUMANAGER_HH

#include <list>
#include "GuiMenu.hpp"

class GuiMenu;

class GuiMenuManager {
protected:
    std::list<GuiMenu*> _menus;
    GuiMenu *_currentMenu;
public:
    GuiMenuManager();
    virtual ~GuiMenuManager();

    GuiMenu *getCurrentMenu() const;

    void addMenu(GuiMenu* menu);
    GuiMenu *getMenu(std::string const &name) const;

    void goToMenu(std::string const &);
    void goToMenu(GuiMenu *);
};


#endif //TESTCEGUI_GUIMENUMANAGER_HH
