//
// Created by debruy_p on 06/05/16.
//

#include "JoinGameMenu.hh"
#include "TutorialApplication.h"
#include "ServerException.hh"

JoinGameMenu::JoinGameMenu():GuiMenu("JoinGameMenu") {

    //
    /// StaticText Enter server ip
    //

    ipStaticText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "JoinGameMenu/IpStaticText");
    ipStaticText->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
    ipStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.35, 0)));
    _root->addChild(ipStaticText);

    //
    /// TextBox IP
    //

    ipEditBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Editbox", "JoinGameMenu/IpEditBox");
    ipEditBox->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
    ipEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.40, 0)));
    _root->addChild(ipEditBox);

    //
    /// StaticText Enter server port
    //

    portStaticText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "JoinGameMenu/PortStaticText");
    portStaticText->setSize(CEGUI::USize(CEGUI::UDim(0.10, 0), CEGUI::UDim(0.05, 0)));
    portStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.60, 0), CEGUI::UDim(0.35, 0)));
    _root->addChild(portStaticText);

    //
    /// TextBox Port
    //

    portEditBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Editbox", "JoinGameMenu/PortEditBox");
    portEditBox->setSize(CEGUI::USize(CEGUI::UDim(0.10, 0), CEGUI::UDim(0.05, 0)));
    portEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.60, 0), CEGUI::UDim(0.40, 0)));
    _root->addChild(portEditBox);

    //
    /// StaticText Enter server mdp
    //

    mdpStaticText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "JoinGameMenu/MdpStaticText");
    mdpStaticText->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    mdpStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.45, 0)));
    _root->addChild(mdpStaticText);

    //
    /// TextBox MDP
    //

    mdpEditBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Editbox", "JoinGameMenu/MdpEditBox");
    mdpEditBox->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    mdpEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.50, 0)));
    _root->addChild(mdpEditBox);

    //
    /// Error text
    //

    errortext = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "EditProfileMenu/Text");
    errortext->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    errortext->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.55, 0)));
    _root->addChild(errortext);

    //
    /// Button Connect
    //

    connectButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "JoinGameMenu/ConnectButton");
    connectButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    connectButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.60, 0)));
    connectButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&JoinGameMenu::connect, this));
    _root->addChild(connectButton);

    //
    /// Button Back
    //
    backButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "JoinGameMenu/BackButton");
    backButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    backButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.70, 0)));
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&JoinGameMenu::back, this));
    _root->addChild(backButton);
}

JoinGameMenu::~JoinGameMenu() {

}

void JoinGameMenu::keyPressed(const OIS::KeyEvent &arg) {
    switch (arg.key){
        case (OIS::KC_ESCAPE):
            back();
            break;
        case (const OIS::KeyCode) (28): //ENTER
            connect();
            break;
        case (OIS::KC_TAB):
            if (ipEditBox->isActive()) {
                ipEditBox->deactivate();
                portEditBox->activate();
            }
            else if (portEditBox->isActive()) {
                portEditBox->deactivate();
                mdpEditBox->activate();
            }
            else if (mdpEditBox->isActive()) {
                mdpEditBox->deactivate();
                ipEditBox->activate();
            }
            break;
    }
}

bool JoinGameMenu::back() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
    return false;
}

void JoinGameMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    ipStaticText->setText(lang->getString("EnterServerIP"));
    portStaticText->setText(lang->getString("EnterPort"));
    mdpStaticText->setText(lang->getString("EnterPassword"));
    errortext->setText("");
    connectButton->setText(lang->getString("Connect"));
    backButton->setText(lang->getString("Back"));

    ipEditBox->activate();

    ipEditBox->setText("127.0.0.1");
    portEditBox->setText("4242");
    mdpEditBox->setText("caca");
}

bool JoinGameMenu::connect() {
    if (!ipEditBox->getText().empty() && !portEditBox->getText().empty()) {
        Server *server;
        try {
            int port = std::stoi(portEditBox->getText().c_str());
            server = new Server(ipEditBox->getText().c_str(), (uint16_t) port,
                                        mdpEditBox->getText().c_str());
            errortext->setText("");
            TutorialApplication::getSingleton().setServer(server);
            TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("SaloonMenu");

            //go to saloon
        }
        catch (ServerException &e){
            errortext->setText(e.what());
        }
        catch (std::invalid_argument &e) {
            errortext->setText(TutorialApplication::getSingleton().getLanguageManager()->getString("PortError"));
        }
    }
    return false;
}



