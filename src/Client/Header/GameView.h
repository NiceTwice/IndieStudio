//
// Created by nicetwice on 18/05/16.
//

#ifndef TESTCEGUI_GAMEVIEW_H
#define TESTCEGUI_GAMEVIEW_H

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <OGRE/SdkCameraMan.h>
#include <OGRE/SdkTrays.h>
#include "GuiMenu.hpp"
#include "Creature.h"
#include "Order.hh"
#include "Thread.hpp"
#include "Spell.h"
#include "TutorialApplication.h"
#include "Warrior.h"
#include "GameHUDManager.h"
#include "View.hpp"
#include "SoundManager.hh"
#include "WorldStaticObject.h"

class GameView :  public View {
    struct addWordldObject{
        float      x;
        float      y;
        float      z;
    };
    struct addPartyMember {
        size_t      controlledCreatureId;
        char        name[50];
    };
    struct setHpMp {
        size_t      creatureId;
        size_t      currentHp;
        size_t      currentMp;
    };
    struct setSpellToUse {
        size_t      spellType;
        size_t      target;
    };
    struct useSpell {
        size_t      spellType;
        size_t      casterId;
        size_t      targetId;
    };
    struct moveTo {
        float       x;
        float       y;
        float       z;
    };
    struct newCreature {
        size_t          type;
        size_t          creatureId;
        float           posX;
        float           posY;
        float           posZ;
        size_t          hp;
        size_t          mp;
    };
    struct setMoveToDirection {
        size_t              id;
        float               x;
        float               y;
        float               z;
    };
    struct RespawnCreature {
        size_t              id;
        float               x;
        float               y;
        float               z;
    };
    struct  changeCreatureDirection {
        size_t                  id;
        float                   posX;
        float                   posY;
        float                   posZ;
        float                   dirX;
        float                   dirY;
        float                   dirZ;
    };
    struct setBuffOnCreature {
        size_t              target;
        size_t              type;
    };
protected:
    Ogre::Camera*                       mCamera;
    Ogre::SceneManager*                 mSceneMgr;
    Ogre::RenderWindow*                 mWindow;
    std::list<IND::Creature*>           creatures;
    std::list<IND::Creature*>           players;
    std::list<IND::WorldStaticObject*>  staticObjects;
    Ogre::RaySceneQuery                 *mRaySceneQuery;

    bool                                _isRunning;
    Ogre::SceneNode                     *curs;

    Ogre::Vector3                       currentTarget;

    Ogre::Entity                *mTargetCursor;
    IND::Creature               *targetCreature;
    IND::Creature               *Controlled;

    GameHUDManager                      *_HUDManager;
public:
    GameView();
    virtual ~GameView();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    void keyPressed(const OIS::KeyEvent &arg);
    void keyReleased(const OIS::KeyEvent &arg );
    void mouseMoved(const OIS::MouseEvent &arg );
    void mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void onCreate();
    void onDestroy();

public:
    IND::Creature       *getTargetCreature(void);
    IND::Creature       *getControlledCreature(void);
    void                addCreature(Order::t_order const &);
    IND::Creature       *getCreatureById(size_t id);
    IND::Creature       *getPlayerById(size_t id);
    IND::Creature       *getCreatureByNode(Ogre::SceneNode *);
    IND::Creature       *findCreatureEverywhereById(size_t id);
    void                treatCreatureDirectionChange(Order::t_order const &);
    void                setControlledCreature(Order::t_order const &cr);
    void                treatUseSpellOrder(Order::t_order const &cr);
    void                treatSetHpMpOrder(Order::t_order const &cr);
    void                treatAddPartyMember(Order::t_order const &cr);
    void                treatSetDeadCreatureOrder(Order::t_order const &cr);
    void                treatErrorMessageOrder(Order::t_order const &cr);
    void                treatRespawnCreatureOrder(Order::t_order const &cr);
    void                treatSetBuffOnCreatureOrder(Order::t_order const &cr);
    void                treatAddWorldObjectOrder(Order::t_order const &cr);
    bool                isRunning(void) const;
};


#endif //TESTCEGUI_GAMEVIEW_H
