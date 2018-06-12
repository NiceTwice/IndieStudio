//
// Created by nicetwice on 18/05/16.
//

#ifndef TESTCEGUI_GAMEHUDMANAGER_H
#define TESTCEGUI_GAMEHUDMANAGER_H

#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include "Creature.h"

class GameHUDManager {
    CEGUI::Window                                   *_controlledBars;
    CEGUI::Window                                   *_allysRootWindow;
    CEGUI::Window                                   *_HUDRootWindow;
    CEGUI::Window                                   *_targetBars;
    CEGUI::Window                                   *_errorWindow;

    std::map<IND::Spell*, CEGUI::Window*>           _spellMap;
    CEGUI::Window                                   *_spellBarWindow;
    CEGUI::Window                                   *_winWindow;
    IND::Creature                                   *_targetCreature;
    IND::Creature                                   *_controlledCreature;
    std::map<IND::Creature*, CEGUI::Window*>        _allyBars;

    CEGUI::WindowManager                            &_wmgr;

    std::string                                     _errorMessage;
public:
    GameHUDManager();
    ~GameHUDManager();
    bool init();
    bool destroy(void);
    void update();
    void addPartyMember(IND::Creature *creature, std::string const &name);
    void setControlledCreature(IND::Creature *creature);
    void setTargetCreature(IND::Creature *creature);
    void initSpellBar(void);
    void updateSpellBar(void);
    void setErrorMessage(std::string const &message);
    void enableWinWindow(bool state);
};


#endif //TESTCEGUI_GAMEHUDMANAGER_H
