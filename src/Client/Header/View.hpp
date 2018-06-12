//
// Created by debruy_p on 23/05/16.
//

#ifndef TESTCEGUI_VIEW_HPP
#define TESTCEGUI_VIEW_HPP

#include <OgreFrameListener.h>
#include <OIS/OIS.h>

class View {
public:
    virtual ~View() {}

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

    virtual void keyPressed(const OIS::KeyEvent &arg) = 0;
    virtual void keyReleased(const OIS::KeyEvent &arg ) = 0;
    virtual void mouseMoved(const OIS::MouseEvent &arg ) = 0;
    virtual void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
    virtual void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
};

#endif //TESTCEGUI_VIEW_HPP