//
// Created by debruy_p on 24/05/16.
//

#include "ViewManager.hh"
#include "GameView.h"
#include "MenuView.hh"

ViewManager::ViewManager() {
    _current = new MenuView();
    _current->onCreate();
    _type = 0;
    _doChange = false;
}

ViewManager::~ViewManager() {
    _current->onDestroy();
    delete _current;
}

void ViewManager::goToGame() {
    if (_type != 1) {
        _type = 1;
        _doChange = true;
    }
}

void ViewManager::goToMenu() {
    if (_type != 0) {
        _type = 0;
        _doChange = true;
    }
}

View *ViewManager::getView() const {
    return _current;
}

void ViewManager::updateMenu(const Ogre::FrameEvent &evt)
{
  if (_type == 0)
    _current->frameRenderingQueued(evt);
}

void ViewManager::change() {
    if (_doChange) {
        _current->onDestroy();
        delete _current;
        if (_type == 0)
            _current = new MenuView();
        else if (_type == 1)
            _current = new GameView();
        _current->onCreate();
        _doChange = false;
    }
}

