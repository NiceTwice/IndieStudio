//
// Created by debruy_p on 24/05/16.
//

#ifndef TESTCEGUI_VIEWMANAGER_HH
#define TESTCEGUI_VIEWMANAGER_HH


#include "View.hpp"

class ViewManager {
protected:
    View    *_current;
    int     _type;
    bool    _doChange;
public:
    ViewManager();
    virtual ~ViewManager();

  void updateMenu(const Ogre::FrameEvent &);
  void goToGame();
    void goToMenu();
    void change();

    View *getView() const;
};


#endif //TESTCEGUI_VIEWMANAGER_HH
