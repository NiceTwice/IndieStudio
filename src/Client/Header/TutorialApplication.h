//
// Created by debruy_p on 05/05/16.
//

/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.hh"
#include "GuiMenuManager.hh"
#include "ProfileManager.hh"
#include "LanguageManager.hh"
#include "Server.hh"
#include "View.hpp"
#include "ViewManager.hh"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/System.h>
#include <CEGUI/PropertyHelper.h>
#include <OIS/OIS.h>
#include <OGRE/Ogre.h>
#include <chrono>

class TutorialApplication : public BaseApplication
{
protected:
    GuiMenuManager *_guiMenuManager;
    ProfileManager *_profileManager;
    LanguageManager *_languageManager;
    Server *_server;
    ViewManager     *_viewManager;
public:
    static TutorialApplication& getSingleton();

private:
    TutorialApplication& operator= (const TutorialApplication&){}
    TutorialApplication (const TutorialApplication&){}

    static TutorialApplication m_instance;

	TutorialApplication(void);
	virtual ~TutorialApplication(void);

protected:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);


    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

public:
    virtual void createScene(void);
    GuiMenuManager *getGuiMenuManager() const;
    ProfileManager *getProfileManager() const;
    LanguageManager *getLanguageManager() const;
    ViewManager *getViewManager() const;
    Server *getServer() const;
    void setServer(Server *);
    void deconnectServer();
    void stop();


    Ogre::Root *getRoot();
    Ogre::RenderWindow *getWindow();


	std::chrono::time_point<std::chrono::high_resolution_clock> const getTimeMillis(void) const;

	float diffTime(std::chrono::time_point<std::chrono::high_resolution_clock> const &now,
						   std::chrono::time_point<std::chrono::high_resolution_clock> const &last) {
		long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
		return ((float)microseconds / 1000000.0f);
	}
};

#endif // #ifndef __TutorialApplication_h_