//
// Created by debruy_p on 08/05/16.
//

#include "SaloonMenu.hh"
#include "TutorialApplication.h"
#include "SoundManager.hh"

SaloonMenu::SaloonMenu():GuiMenu("SaloonMenu"), users(NULL) {

    //
    /// Server Name
    //

    serverName = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "SaloonMenu/ServerName");
    serverName->setSize(CEGUI::USize(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    serverName->setPosition(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.10, 0)));
    _root->addChild(serverName);
    //
    /// Chat
    //

    chat = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "SaloonMenu/Chat");
    chat->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(1.0, 0)));
    chat->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7, 0), CEGUI::UDim(0.00, 0)));
    _root->addChild(chat);

    //
    /// ChatBox
    //

    chatBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/MultiLineEditbox", "SaloonMenu/ChatBox");
    chatBox->setSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(0.90, 0)));
    chatBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0, 0), CEGUI::UDim(0.0, 0)));
    (dynamic_cast<CEGUI::MultiLineEditbox*>(chatBox))->setReadOnly(true);
    chat->addChild(chatBox);

    //
    /// Chat EditBox
    //

    chatEditBox = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Editbox", "SaloonMenu/ChatEditBox");
    chatEditBox->setSize(CEGUI::USize(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.05, 0)));
    chatEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0, 0), CEGUI::UDim(0.90, 0)));
    chat->addChild(chatEditBox);

    //
    /// Button Send
    //

    sendButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "SaloonMenu/SendButton");
    sendButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    sendButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.90, 0)));
    sendButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SaloonMenu::send, this));
    chat->addChild(sendButton);

    //
    /// Start Button
    //

    startButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "SaloonMenu/StartButton");
    startButton->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
    startButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.90, 0)));
    startButton->setVisible(false);
    startButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SaloonMenu::create, this));
    _root->addChild(startButton);

    //
    /// Exit Button
    //

    exitButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "SaloonMenu/ExitButton");
    exitButton->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    exitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.01, 0), CEGUI::UDim(0.90, 0)));
    exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SaloonMenu::back, this));
    _root->addChild(exitButton);
}

SaloonMenu::~SaloonMenu() {

}

void SaloonMenu::onDisplay() {
    exitButton->setText(TutorialApplication::getSingleton().getLanguageManager()->getString("Quit"));
    serverName->setText(TutorialApplication::getSingleton().getServer()->getName());
    sendButton->setText(TutorialApplication::getSingleton().getLanguageManager()->getString("Send"));
    startButton->setText(TutorialApplication::getSingleton().getLanguageManager()->getString("StartGame"));
    startButton->setVisible(false);
    chatBox->setText("");
    chatEditBox->setText("");
    _type = 0;
}

void SaloonMenu::onUnDisplay() {

}

void SaloonMenu::keyPressed(const OIS::KeyEvent &arg) {
    switch (arg.key){
        case (OIS::KC_ESCAPE):
            back();
            break;
        case (const OIS::KeyCode) (28): //ENTER
            if (!chatEditBox->isActive())
                chatEditBox->activate();
            else {
                send();
            }
            break;
    }
}

bool SaloonMenu::back() {
    TutorialApplication::getSingleton().getServer()->deconnect();
    TutorialApplication::getSingleton().deconnectServer();
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
}

bool SaloonMenu::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    Server *server = TutorialApplication::getSingleton().getServer();
    server->communication();
    while (TutorialApplication::getSingleton().getServer() && server->haveOrderToTreat() && this == TutorialApplication::getSingleton().getGuiMenuManager()->getCurrentMenu()){
        switch (*server->getOrderToTreat().type) {
            case (Order::TYPE::CHAT):
                getChatMessage(server->getOrderToTreat());
                break;
            case (Order::TYPE::HOST):
                host();
                break;
            case (Order::TYPE::PING):
                getPing(server->getOrderToTreat());
                break;
            case (Order::TYPE::DECONNECT):
                TutorialApplication::getSingleton().deconnectServer();
                TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
                break;
            case (Order::TYPE::PROFIL):
                getProfiles(server->getOrderToTreat());
                break;
            case (Order::TYPE::STARTGAME) :
                startGame();
                server->orderTreated();
                return true;
                break;

        }
        if (TutorialApplication::getSingleton().getServer())
            server->orderTreated();
        else
            break;
    }
    return true;
}

bool SaloonMenu::send() {
    if (!chatEditBox->getText().empty()) {
        TutorialApplication::getSingleton().getServer()->stockOrderToSend(new Order(Order::TYPE::CHAT, chatEditBox->getText().size() + 1, (void*)chatEditBox->getText().c_str()));
        chatEditBox->setText("");
    }
    chatEditBox->deactivate();
    return false;
}

bool SaloonMenu::create() {
    TutorialApplication::getSingleton().getServer()->stockOrderToSend(new Order(Order::TYPE::STARTGAME, 0, NULL));
    return false;
}

void SaloonMenu::getChatMessage(Order::t_order const &order) {
    std::string msg = (char*)order.data;
    (dynamic_cast<CEGUI::MultiLineEditbox*>(chatBox))->appendText(msg + "\n");
}

void SaloonMenu::getPing(Order::t_order const &order) {
    std::chrono::time_point<std::chrono::high_resolution_clock> *stime = (std::chrono::time_point<std::chrono::high_resolution_clock> *)order.data;
    std::string ping = std::to_string(TutorialApplication::getSingleton().diffTime(TutorialApplication::getSingleton().getTimeMillis(), *stime));
}

void SaloonMenu::getProfiles(Order::t_order const &order) {


    //
    /// Users
    //
    if (users){
        users->destroy();
    }
    users = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "SaloonMenu/Users");
    users->setSize(CEGUI::USize(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.70, 0)));
    users->setPosition(CEGUI::UVector2(CEGUI::UDim(0.10, 0), CEGUI::UDim(0.20, 0)));
    _root->addChild(users);

    char *data = (char*)order.data;
    uint8_t *nb = (uint8_t *)order.data;
    uint8_t *place = (uint8_t *)order.data + sizeof(uint8_t);
    char *curs = data + (2 * sizeof(uint8_t));

    CEGUI::Window *user;
    CEGUI::Window *username;
    for (uint8_t i = 0; i < *nb; ++i) {

        //
        /// User BOX
        //
        user = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticImage",
                                                                 "SaloonMenu/User" + std::to_string(i));
        user->setSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(0.15, 0)));
        user->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0, 0), CEGUI::UDim((float) (0.20 * i), 0)));
        users->addChild(user);

        //
        /// User name
        //
        username = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText",
                                                                     "SaloonMenu/UserName" + std::to_string(i));
        username->setSize(CEGUI::USize(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.99, 0)));
        username->setPosition(CEGUI::UVector2(CEGUI::UDim(0.10, 0), CEGUI::UDim(0.0, 0)));
        username->setText(curs);
        user->addChild(username);

        if (i == *place) {
            charac = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Combobox",
                                                                       "SaloonMenu/Character" + std::to_string(i));
            charac->setSize(CEGUI::USize(CEGUI::UDim(0.30, 0), CEGUI::UDim(10, 0)));
            charac->setPosition(CEGUI::UVector2(CEGUI::UDim(0.65, 0), CEGUI::UDim(0.30, 0)));
            charac->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&SaloonMenu::onChangeCharac, this));
            static_cast<CEGUI::Combobox *>(charac)->setReadOnly(true);
            static_cast<CEGUI::Combobox *>(charac)->setAutoSizeListHeightToContent(true);
            static_cast<CEGUI::Combobox *>(charac)->setAutoSizeListWidthToContent(true);

            CEGUI::ListboxTextItem *itemCombobox;

            itemCombobox = new CEGUI::ListboxTextItem(TutorialApplication::getSingleton().getLanguageManager()->getString("Warrior"), 1);
            static_cast<CEGUI::Combobox *>(charac)->addItem(itemCombobox);

            itemCombobox = new CEGUI::ListboxTextItem(TutorialApplication::getSingleton().getLanguageManager()->getString("BowMan"), 2);
            static_cast<CEGUI::Combobox *>(charac)->addItem(itemCombobox);

            itemCombobox = new CEGUI::ListboxTextItem(TutorialApplication::getSingleton().getLanguageManager()->getString("Mage"), 3);
            static_cast<CEGUI::Combobox *>(charac)->addItem(itemCombobox);

            itemCombobox = new CEGUI::ListboxTextItem(TutorialApplication::getSingleton().getLanguageManager()->getString("Assassin"), 4);
            static_cast<CEGUI::Combobox *>(charac)->addItem(itemCombobox);

            //static_cast<CEGUI::Combobox *>(charac)->setText(static_cast<CEGUI::Combobox *>(charac)->getListboxItemFromIndex((size_t) _type)->getText());
            static_cast<CEGUI::Combobox *>(charac)->clearAllSelections();
            if (static_cast<CEGUI::Combobox *>(charac)->getSelectedItem())
                static_cast<CEGUI::Combobox *>(charac)->setItemSelectState(static_cast<CEGUI::Combobox *>(charac)->getSelectedItem(), false);
            static_cast<CEGUI::Combobox *>(charac)->setItemSelectState(static_cast<CEGUI::Combobox *>(charac)->getListboxItemFromIndex((size_t) _type), true);
            user->addChild(charac);
        }

        curs += PROFILELEN;
    }
}

void SaloonMenu::host() {
    startButton->setVisible(true);
}

void SaloonMenu::startGame() {
    SoundManager &sm = SoundManager::getSingleton();
    sm.stopAmbiance();
    sm.setAmbiance("Sound/worakls.mp3");
    sm.playAmbiance();
    TutorialApplication::getSingleton().getViewManager()->goToGame();
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("GameMenu");
}

bool SaloonMenu::onChangeCharac() {
    size_t nb = static_cast<CEGUI::Combobox *>(charac)->getSelectedItem()->getID();
    _type = nb - 1;
    TutorialApplication::getSingleton().getServer()->stockOrderToSend(new Order(Order::TYPE::ChangeCharac, sizeof(size_t), &nb));
}
