//
// Created by nicetwice on 18/05/16.
//

#include "GameHUDManager.h"
#include "ObjectFactory.hpp"


GameHUDManager::GameHUDManager(): _wmgr(CEGUI::WindowManager::getSingleton()){

    _controlledCreature = NULL;
    _targetCreature = NULL;
}

GameHUDManager::~GameHUDManager() {
    delete _controlledBars;
    delete _spellBarWindow;
    delete _allysRootWindow;
    delete _targetBars;
    delete _errorWindow;
}

void GameHUDManager::update() {
    if (_controlledCreature) {
        ((CEGUI::ProgressBar *) _controlledBars->getChild("hpbar"))->setProgress(
                (float) _controlledCreature->getHp() / (float) _controlledCreature->getMaxHp());
        ((CEGUI::ProgressBar *) _controlledBars->getChild("mpbar"))->setProgress(
                (float) _controlledCreature->getMp() / (float) _controlledCreature->getMaxMp());
        _controlledBars->getChild("hpbar")->getChild("text")->setText(IND::ObjectFactory::WHITE + _controlledCreature->getCurrentHpStr());
        _controlledBars->getChild("mpbar")->getChild("text")->setText(IND::ObjectFactory::WHITE + _controlledCreature->getCurrentMpStr());
    }
    if (_targetCreature) {
        _targetBars->setVisible(true);
        ((CEGUI::ProgressBar *) _targetBars)->setProgress(
                (float) _targetCreature->getHp() / (float) _targetCreature->getMaxHp());
    }
    else{
        _targetBars->setVisible(false);
    }
    for (auto j = _allyBars.begin(); j != _allyBars.end(); ++j) {
        ((CEGUI::ProgressBar*)(*j).second->getChild("hpbar"))->setProgress((float)((*j).first->getHp()) / (float)((*j).first)->getMaxHp());
        ((CEGUI::ProgressBar*)(*j).second->getChild("mpbar"))->setProgress((float)((*j).first->getMp()) / (float)((*j).first)->getMaxMp());
    }
    _errorWindow->setText(_errorMessage);
    updateSpellBar();
}

bool GameHUDManager::init() {
    CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
    //CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("Spells.scheme");
    _HUDRootWindow = _wmgr.createWindow("DefaultWindow", "HUDRootWindow");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_HUDRootWindow);

    _winWindow = _wmgr.createWindow("OgreTray/AltStaticImage", "WinWindow");
    _winWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.2, 0.0)));
    _winWindow->setSize(CEGUI::USize(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.2, 0)));
    _winWindow->setProperty("Image", "SpellIcons/YouWinScreen");
    _HUDRootWindow->addChild(_winWindow);
    _winWindow->setVisible(false);
    _winWindow->setEnabled(false);
    //target creature bars (only health for now)
    _targetBars = _wmgr.createWindow("OgreTray/ProgressBar", "TargetBars");
    _targetBars->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.05, 0.0)));
    _targetBars->setSize(CEGUI::USize(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.05, 0)));
    _HUDRootWindow->addChild(_targetBars);
    _targetBars->setVisible(false);

    //Error message window
    _errorWindow = _wmgr.createWindow("AlfiskoSkin/Label", "ErrorMessage");
    _errorWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.80, 0.0)));
    _errorWindow->setSize(CEGUI::USize(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.05, 0)));
    _HUDRootWindow->addChild(_errorWindow);

    //Controlled Creature bars
    _controlledBars = _wmgr.createWindow("DefaultWindow", "ControlledBars");
    _controlledBars->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.9, 0.0)));
    _controlledBars->setSize(CEGUI::USize(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.1, 0)));
    CEGUI::Window *hpbar = _wmgr.createWindow("OgreTray/ProgressBar","hpbar");
    ((CEGUI::ProgressBar *) hpbar)->setProgress(0.5);
    hpbar->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0.0)));
    hpbar->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.5, 0)));
    _controlledBars->addChild(hpbar);
    CEGUI::Window *hptext = _wmgr.createWindow("AlfiskoSkin/Label", "text");
    hpbar->addChild(hptext);
    hptext->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
    hptext->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));

    CEGUI::Window *manabar = _wmgr.createWindow("OgreTray/ManaBar","mpbar");
    ((CEGUI::ProgressBar *) manabar)->setProgress(0.5);
    manabar->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.5, 0.0)));
    manabar->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.5, 0)));
    _controlledBars->addChild(manabar);
    CEGUI::Window *manatext = _wmgr.createWindow("AlfiskoSkin/Label", "text");
    manabar->addChild(manatext);
    manatext->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));
    manatext->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
    _HUDRootWindow->addChild(_controlledBars);

    //spell bar window
    _spellBarWindow = _wmgr.createWindow("DefaultWindow", "SpellBar");
    _spellBarWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.42, 0), CEGUI::UDim(0.85, 0.0)));
    _spellBarWindow->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    _HUDRootWindow->addChild(_spellBarWindow);

    //allys bars left
    _allysRootWindow = _wmgr.createWindow("OgreTray/Label", "AllyBars");
    _allysRootWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.3, 0.0)));
    _allysRootWindow->setSize(CEGUI::USize(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.4, 0)));
    _HUDRootWindow->addChild(_allysRootWindow);

    return false;
}

bool GameHUDManager::destroy(void) {
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(_HUDRootWindow);
    return false;
}

void GameHUDManager::addPartyMember(IND::Creature *creature, std::string const &playerName) {
    CEGUI::Window *ally1 = _wmgr.createWindow("DefaultWindow");
    ally1->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.25f * _allyBars.size(), 0.0)));
    ally1->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.2, 0)));
    CEGUI::Window *allyHead = _wmgr.createWindow("OgreTray/StaticImage", "head");
    allyHead->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
    allyHead->setSize(CEGUI::USize(CEGUI::UDim(0.3, 0), CEGUI::UDim(1, 0)));
//    allyHead->setProperty("Image", "OgreTray/CloseButtonNormal");
    CEGUI::Window *name = _wmgr.createWindow("OgreTray/Label", "name");
    name->setPosition(CEGUI::UVector2(CEGUI::UDim(0.31, 0), CEGUI::UDim(0, 0)));
    name->setSize(CEGUI::USize(CEGUI::UDim(0.69, 0), CEGUI::UDim(0.3, 0)));
    name->setText(playerName);
    ally1->addChild(name);
    CEGUI::Window *allyManabar = _wmgr.createWindow("OgreTray/ProgressBar", "hpbar");
    ((CEGUI::ProgressBar *) allyManabar)->setProgress(0.8);
    allyManabar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.3, 0.0)));
    allyManabar->setSize(CEGUI::USize(CEGUI::UDim(0.7, 0), CEGUI::UDim(0.35, 0)));
    ally1->addChild(allyManabar);
    allyManabar = _wmgr.createWindow("OgreTray/ManaBar", "mpbar");
    ((CEGUI::ProgressBar *) allyManabar)->setProgress(0.4);
    allyManabar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.65, 0.0)));
    allyManabar->setSize(CEGUI::USize(CEGUI::UDim(0.7, 0), CEGUI::UDim(0.35, 0)));
    ally1->addChild(allyManabar);
    ally1->addChild(allyHead);

    _allysRootWindow->addChild(ally1);
    ally1->setVisible(true);
    _allyBars.insert(std::pair<IND::Creature*, CEGUI::Window*>(creature, ally1));
}

void GameHUDManager::setControlledCreature(IND::Creature *creature) {
    _controlledCreature = creature;
    initSpellBar();
}

void GameHUDManager::setTargetCreature(IND::Creature *creature) {
    _targetCreature = creature;
}

void GameHUDManager::initSpellBar(void) {
    size_t          nbSpells = 0;
    CEGUI::Window   *tmpWindow;
    CEGUI::Window   *cd;

    if (_controlledCreature){
        while (_controlledCreature->getSpellByNumber(nbSpells)){
            nbSpells++;
        }
        for (size_t j = 0; j < nbSpells; ++j) {
            tmpWindow = _wmgr.createWindow("OgreTray/AltStaticImage");
            tmpWindow->setPosition(CEGUI::UVector2(CEGUI::UDim((1.0f / 3.0f) * (float)j, 0), CEGUI::UDim(0, 0.0)));
            tmpWindow->setSize(CEGUI::USize(CEGUI::UDim((1.0f / 3.0f), 0), CEGUI::UDim(1, 0)));
            tmpWindow->setProperty("Image", _controlledCreature->getSpellByNumber(j)->getImageName());
            _spellBarWindow->addChild(tmpWindow);
            cd = _wmgr.createWindow("AlfiskoSkin/Label","CD");
            cd->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0.0)));
            cd->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));
            cd->setText("");
            tmpWindow->addChild(cd);
            _spellMap.insert(std::pair<IND::Spell*, CEGUI::Window*>(_controlledCreature->getSpellByNumber(j), tmpWindow));
        }
    }
}

void GameHUDManager::updateSpellBar(void) {
    std::map<IND::Spell*, CEGUI::Window*>::iterator     it = _spellMap.begin();
    IND::Spell              *spell;
    CEGUI::Window           *win;
    CEGUI::Window           *cd;
    std::stringstream       ss;

    while (it != _spellMap.end()){
        ss.str("");
        spell = (*it).first;
        win = (*it).second;
        cd = win->getChild("CD");

        if (spell->getCurrentCd() > 0){
            ss << "[colour='FFFFFFFF']" << std::setprecision(2) << spell->getCurrentCd();
            cd->setText(ss.str());
        }
        else
            cd->setText("");
        it++;
    }
}

void GameHUDManager::setErrorMessage(std::string const &message) {
    _errorMessage = message;
}

void GameHUDManager::enableWinWindow(bool state){
    _winWindow->setEnabled(state);
    _winWindow->setVisible(state);
}

