//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_AGUIMENU_HPP
#define TESTCEGUI_AGUIMENU_HPP

#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <OIS.h>
#include <OgreFrameListener.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include <OGRE/SdkTrays.h>
#include <OGRE/SdkCameraMan.h>
#include "GuiMenuManager.hh"

class GuiMenuManager;

class GuiMenu {
protected:
    CEGUI::Window *_root;
public:
    GuiMenu(std::string const &name) {
        _root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", name);
        _root->setSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(1.0, 0)));
    }
    virtual ~GuiMenu(){

    }

    CEGUI::Window *getRoot() const {
        return _root;
    }

    CEGUI::Window *getWindow(std::string const &name) const {
        return (_root->getChild(name));
    }

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) {}

    virtual void keyPressed(const OIS::KeyEvent &arg) {}
    virtual void keyReleased(const OIS::KeyEvent &arg ) {}
    virtual void mouseMoved(const OIS::MouseEvent &arg ) {}
    virtual void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {}
    virtual void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {}

    virtual void onDisplay() {}
    virtual void onUnDisplay() {}
};

#endif //TESTCEGUI_AGUIMENU_HPP
