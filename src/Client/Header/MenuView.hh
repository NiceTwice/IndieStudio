//
// Created by debruy_p on 24/05/16.
//

#ifndef TESTCEGUI_MENUVIEW_HH
#define TESTCEGUI_MENUVIEW_HH


#include <OgreFrameListener.h>
#include "View.hpp"
#include "Creature.h"
class MenuView : public View {
protected:
    Ogre::Camera*                       mCamera;
    Ogre::SceneManager*                 mSceneMgr;
    std::vector<IND::Creature*>         creatures;
    std::vector<Ogre::Entity*>          entitys;
public:
    MenuView();
    virtual ~MenuView();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    void keyPressed(const OIS::KeyEvent &arg);
    void keyReleased(const OIS::KeyEvent &arg );
    void mouseMoved(const OIS::MouseEvent &arg );
    void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void onCreate();
    void onDestroy();

    void addEntity(std::string const &meshName, Ogre::Vector3 const &pos, Ogre::Vector3 const &scale);
};


#endif //TESTCEGUI_MENUVIEW_HH
