//
// Created by debruy_p on 08/05/16.
//

#ifndef TESTCEGUI_SALOONMENU_HH
#define TESTCEGUI_SALOONMENU_HH


#include "GuiMenu.hpp"
#include "Order.hh"

class SaloonMenu : public GuiMenu{
protected:
    CEGUI::Window *serverName;
    CEGUI::Window *users;
    CEGUI::Window *charac;
    CEGUI::Window *chat;
    CEGUI::Window *chatBox;
    CEGUI::Window *chatEditBox;
    CEGUI::Window *sendButton;
    CEGUI::Window *startButton;
    CEGUI::Window *exitButton;
    int     _type;
public:
    SaloonMenu();
    virtual ~SaloonMenu();

    void onDisplay();
    void onUnDisplay();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    void keyPressed(const OIS::KeyEvent &arg);

private:
    bool send();
    bool back();
    bool create();

    void getChatMessage(Order::t_order const &);
    void host();
    void getPing(Order::t_order const &);
    void getProfiles(Order::t_order const &);
    void startGame();
    bool onChangeCharac();
};

#endif //TESTCEGUI_SALOONMENU_HH
