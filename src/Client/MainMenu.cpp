//
// Created by debruy_p on 06/05/16.
//

#include <ServerException.hh>
#include "MainMenu.hh"
#include "TutorialApplication.h"
#include "SoundManager.hh"

MainMenu::MainMenu(): GuiMenu("MainMenu") {

  /*
   * Initialize sounds
   */
  SoundManager &sm = SoundManager::getSingleton();
  sm.setAmbiance("Sound/acdc.mp3");
  sm.createSound("Sound/FireBall.wav", "FireBall");
  sm.createSound("Sound/applause.wav", "applause");
  sm.createSound("Sound/heal.wav", "heal");
  sm.createSound("Sound/sword.wav", "sword");
  sm.createSound("Sound/death.wav", "death");
  sm.playAmbiance();
    //
    /// Button Create Game
    //

    _createGameButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "MainMenu/CreateGameButton");
    _createGameButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    _createGameButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.40, 0)));
    _createGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::createGame, this));
    _root->addChild(_createGameButton);

    //
    /// Button Join Game
    //

    _joinGameButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "MainMenu/JoinGameButton");
    _joinGameButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    _joinGameButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.50, 0)));
    _joinGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::joinGame, this));
    _root->addChild(_joinGameButton);

    //
    /// Button Options
    //

    _optionsButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "MainMenu/OptionButton");
    _optionsButton->setSize(CEGUI::USize(CEGUI::UDim(0.18, 0), CEGUI::UDim(0.05, 0)));
    _optionsButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.60, 0)));
    _optionsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::options, this));
    _root->addChild(_optionsButton);

    //
    /// Button Profile
    //

    _profileButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "MainMenu/ProfileButton");
    _profileButton->setSize(CEGUI::USize(CEGUI::UDim(0.18, 0), CEGUI::UDim(0.05, 0)));
    _profileButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.52, 0), CEGUI::UDim(0.60, 0)));
    _profileButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::profile, this));
    _root->addChild(_profileButton);

    //
    /// Button Quit
    //

    _quitButton = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/Button", "MainMenu/QuitButton");
    _quitButton->setSize(CEGUI::USize(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.05, 0)));
    _quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.70, 0)));
    _quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::quit, this));
    _root->addChild(_quitButton);

    //
    /// StaticText Welcome
    //

    _text = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "MainMenu/WelcomeText");
    _text->setSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(0.05, 0)));
    _text->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0), CEGUI::UDim(0.90, 0)));
    _root->addChild(_text);
}

MainMenu::~MainMenu() {

}

bool MainMenu::joinGame() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("JoinGameMenu");
    return false;
}

bool MainMenu::options() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("OptionsMenu");
    return false;
}

bool MainMenu::profile() {
    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("ProfileMenu");
    return false;
}

bool MainMenu::quit() {
    TutorialApplication::getSingleton().stop();
    return false;
}

void MainMenu::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
    {
        TutorialApplication::getSingleton().stop();
    }
}

void MainMenu::onDisplay() {
    LanguageManager *lang = TutorialApplication::getSingleton().getLanguageManager();

    _createGameButton->setText(lang->getString("CreateGame"));
    _joinGameButton->setText(lang->getString("JoinGame"));
    _optionsButton->setText(lang->getString("Options"));
    _profileButton->setText(lang->getString("Profile"));
    _quitButton->setText(lang->getString("Quit"));
    _text->setText(lang->getString("Welcome") + " " + TutorialApplication::getSingleton().getProfileManager()->getCurrentProfile()->getName() + "!!");

}

void MainMenu::onUnDisplay() {

}

bool MainMenu::createGame() {
    Server *server;
    if (fork() == 0)
    {
        execlp("./server", "./server", "MyGame", "4242", NULL);
        std::exit(1);
    }
    sleep(1);
    try {
        server = new Server("127.0.0.1", 4242,
                "");
        TutorialApplication::getSingleton().setServer(server);
        TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("SaloonMenu");

    }
    catch (ServerException &e){
    }
    catch (std::invalid_argument &e) {
    }
}


