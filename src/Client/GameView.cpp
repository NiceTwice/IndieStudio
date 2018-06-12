//
// Created by nicetwice on 18/05/16.
//

#include "GameView.h"
#include "BuffSpeedBoostFire.h"
#include "ObjectFactory.hpp"
#include "WorldStaticObject.h"

GameView::GameView(){
    this->Controlled = NULL;
    this->_isRunning = true;
    this->targetCreature = NULL;
    this->_HUDManager = new GameHUDManager();
}

GameView::~GameView() {
    _HUDManager->destroy();
    delete _HUDManager;
}

bool GameView::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    Server *server = TutorialApplication::getSingleton().getServer();
    if (!server->haveOrderToTreat())
        server->communication();
    if (server) {
        while (server->haveOrderToTreat()) {
            switch (*server->getOrderToTreat().type) {
                case (Order::TYPE::CHAT):;
                    break;
                case (Order::TYPE::HOST):;
                    break;
                case (Order::TYPE::PING):;
                    break;
                case (Order::TYPE::DECONNECT):
                    TutorialApplication::getSingleton().deconnectServer();
                    TutorialApplication::getSingleton().getGuiMenuManager()->goToMenu("MainMenu");
                    TutorialApplication::getSingleton().getViewManager()->goToMenu();
                    break;
                case (Order::TYPE::PROFIL):
                    treatAddPartyMember(server->getOrderToTreat());
                    break;
                case (Order::TYPE::NEW_CREATURE):
                    addCreature(server->getOrderToTreat());
                    break;
                case (Order::TYPE::ChangeCreatureDirection):
                    treatCreatureDirectionChange(server->getOrderToTreat());
                    break;
                case (Order::TYPE::SetCreatureToControl):
                    setControlledCreature(server->getOrderToTreat());
                    break;
                case (Order::TYPE::UseSpell):
                    treatUseSpellOrder(server->getOrderToTreat());
                    break;
                case (Order::TYPE::SetHpMp):
                    treatSetHpMpOrder(server->getOrderToTreat());
                    break;
                case (Order::TYPE::SetCreatureDeath):
                    treatSetDeadCreatureOrder(server->getOrderToTreat());
                    break;
                case (Order::TYPE::SetErrorMessage):
                    treatErrorMessageOrder(server->getOrderToTreat());
                    break;
                case (Order::TYPE::RespawnCreature):
                    treatRespawnCreatureOrder(server->getOrderToTreat());
                    break;
                case (Order::TYPE::SetBuffOnCreature):
                    treatSetBuffOnCreatureOrder(server->getOrderToTreat());
                    break;
                case (Order::TYPE::addWorldObject):
                    treatAddWorldObjectOrder(server->getOrderToTreat());
                    break;
            }
            if (TutorialApplication::getSingleton().getServer())
                server->orderTreated();
            else
                break;
        }
        std::list<IND::Creature *>::iterator it = creatures.begin();
        while (it != creatures.end()) {
            (*it)->update(evt);
            if ((*it)->isDead() && (*it)->getDeathTimer() <= 0) {
                if (targetCreature == (*it)) {
                    targetCreature = NULL;
                    mTargetCursor->detachFromParent();
                }
                delete (*it);
                creatures.erase(it);
                it = creatures.begin();
                if (creatures.size() == 0 && players.size() != 0)
		  {
		    SoundManager &sm = SoundManager::getSingleton();
		    sm.playSound("applause");
                    _HUDManager->enableWinWindow(true);
		  }
                else
                    _HUDManager->enableWinWindow(false);
            }
            else
                it++;
        }
        for (auto itr = players.begin(); itr != players.end(); ++itr) {
            (*itr)->update(evt);
        }

        if (Controlled) {
            curs->setVisible(Controlled->isMooving(), true);
            mCamera->setPosition(Ogre::Vector3(0 + Controlled->getSceneNode()->getPosition().x, 1000,
                                               600 + Controlled->getSceneNode()->getPosition().z));
            mCamera->lookAt(Controlled->getSceneNode()->getPosition());
        }
        curs->yaw(Ogre::Degree((float) 360.0 * evt.timeSinceLastFrame));
        _HUDManager->update();
    }
    return true;
}

void GameView::keyPressed(const OIS::KeyEvent &arg) {

}

void GameView::keyReleased(const OIS::KeyEvent &arg) {
    setSpellToUse tmp;
    size_t          nb_spell = 0;
    switch (arg.key){
        case OIS::KC_A :{
            nb_spell = 0;
            break;
        }
        case OIS::KC_Z :{
            nb_spell = 1;
            break;
        }
        case OIS::KC_E :{
            nb_spell = 2;
            break;
        }
        case OIS::KC_R :{
            nb_spell = 3;
            break;
        }
        case OIS::KC_T :{
            nb_spell = 4;
            break;
        }
        default:
            break;
    }
    tmp.target = (targetCreature) ? targetCreature->getSceneId() : Controlled->getSceneId();
    if (Controlled->getSpellByNumber(nb_spell)) {
        tmp.spellType = (size_t) Controlled->getSpellByNumber(nb_spell)->getType();
        TutorialApplication::getSingleton().getServer()->stockOrderToSend(
                new Order(Order::UseSpell, sizeof(GameView::setSpellToUse), &tmp));
    }
}

void GameView::mouseMoved(const OIS::MouseEvent &arg) {

}

void GameView::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {

}
void GameView::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    moveTo   buff;
    switch (id) {
        case OIS::MB_Right: {
            CEGUI::GUIContext &context = CEGUI::System::getSingleton().getDefaultGUIContext();
            CEGUI::Vector2f mousePos = context.getMouseCursor().getPosition();
            Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
            Ogre::Ray selectRay = mCamera->getCameraToViewportRay(mousePos.d_x / (float) arg.state.width,
                                                                  mousePos.d_y / (float) arg.state.height);
            Ogre::Real d = selectRay.intersects(plane).second;
            Ogre::Vector3 position = selectRay.getPoint(d);
            currentTarget = position;
            buff.x = position.x;
            buff.y = 0;
            buff.z = position.z;
            curs->setPosition(currentTarget.x, 5, currentTarget.z);
            curs->setVisible(true);
            TutorialApplication::getSingleton().getServer()->stockOrderToSend(new Order(Order::RightButtonClick, sizeof(moveTo), &buff));
            break;
        }
        case OIS::MB_Left: {
            // Set up the ray scene query
            CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
            CEGUI::Vector2f mousePos = context.getMouseCursor().getPosition();
            Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/(float)arg.state.width, mousePos.d_y/(float)arg.state.height);
            mRaySceneQuery->setRay(mouseRay);
            mRaySceneQuery->setSortByDistance(true);
            mRaySceneQuery->setQueryTypeMask(Ogre::SceneManager::ENTITY_TYPE_MASK);
            Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
            Ogre::RaySceneQueryResult::iterator itr;

            itr = result.begin();
            if (targetCreature != NULL)
                targetCreature->getSceneNode()->detachObject("TargetCursor");
            while (itr != result.end()) {
                if ((targetCreature = getCreatureByNode(itr->movable->getParentSceneNode())) != NULL)
                    break;
                itr++;
            }
            if (targetCreature != NULL && targetCreature != Controlled) {
                targetCreature->getSceneNode()->attachObject(mTargetCursor);
                mTargetCursor->setVisible(true);
            }
            else {
                targetCreature = NULL;
                mTargetCursor->setVisible(false);
            }
            _HUDManager->setTargetCreature(targetCreature);
            break;
        }
        default:
            break;
    }
}

void GameView::onCreate() {
    mSceneMgr = TutorialApplication::getSingleton().getRoot()->createSceneManager(Ogre::ST_GENERIC);
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,1000,600));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(10);
    // Create one viewport, entire window
    Ogre::Viewport* vp = TutorialApplication::getSingleton().getWindow()->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(255,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
            "ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            20000, 20000, 40, 40,
            true,
            1, 120, 120,
            Ogre::Vector3::UNIT_Z);
    Ogre::Entity *groundEntity = mSceneMgr->createEntity("ground", "ground");
    groundEntity->setMaterialName("Examples/GrassFloor");
    mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -0.02, 0))->attachObject(groundEntity);
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    Ogre::MeshManager::getSingleton().createPlane(
            "curs",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            40, 40, 1, 1,
            true,
            1, 1, 1,
            Ogre::Vector3::UNIT_Z);
    Ogre::MeshManager::getSingleton().createPlane(
            "TargetCursor",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            1.5, 1.5, 40, 40,
            true,
            1, 1, 1,
            Ogre::Vector3::UNIT_Z);
    mTargetCursor = mSceneMgr->createEntity("TargetCursor", "TargetCursor");
    mTargetCursor->setMaterialName("MyMaterial/CursorTarget");
    groundEntity = mSceneMgr->createEntity("curs", "curs");
    curs = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 10, 0));
    groundEntity->setMaterialName("MyMaterial/CursorArrows");
    curs->attachObject(groundEntity);
    curs->setVisible(false, true);

    //lights
/*    Ogre::ParticleSystem   *ps = mSceneMgr->createParticleSystem("lala", "MyParticle/Spiral");

    mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 50, 0))->attachObject(ps);

    ps->setVisible(true);
    ps->setEmitting(true);
    */
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    Ogre::Light *spotLight = mSceneMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(1, 1, 1);
    spotLight->setSpecularColour(1, 1, 1);
    spotLight->setType(Ogre::Light::LT_DIRECTIONAL);
    spotLight->setDirection(Ogre::Vector3(-1, -1, -1));
    _HUDManager->init();
}

void GameView::onDestroy() {
    _isRunning = false;
    TutorialApplication::getSingleton().getWindow()->removeViewport(0);
    //TutorialApplication::getSingleton().getRoot().destroySceneManager(mSceneMgr);
}

void GameView::addCreature(Order::t_order const &cr) {
    newCreature      *tmp = (newCreature*)cr.data;

    IND::Creature   *creatureTmp = IND::ObjectFactory::createCreature(tmp->type, Ogre::Vector3(tmp->posX, tmp->posY, tmp->posZ), IND::Entity::Ally, mSceneMgr, tmp->creatureId);
    if (creatureTmp) {
        creatures.push_back(creatureTmp);
        creatureTmp->setCurrentMp(tmp->mp);
        creatureTmp->setCurrentHp(tmp->hp);
    }
}

void GameView::treatCreatureDirectionChange(Order::t_order const &cr) {
    changeCreatureDirection *tmp = (changeCreatureDirection*)cr.data;
    IND::Creature           *creatureTmp;

    creatureTmp = findCreatureEverywhereById(tmp->id);
    if (creatureTmp != NULL){
       creatureTmp->treatPositionAndDirection(Ogre::Vector3(tmp->dirX, tmp->dirY, tmp->dirZ), Ogre::Vector3(tmp->posX, tmp->posY, tmp->posZ));
    }
}

IND::Creature *GameView::getCreatureById(size_t id) {
    std::list<IND::Creature*>::iterator           it = creatures.begin();
    while (it != creatures.end()){
        if ((*it) != NULL && id == (*it)->getSceneId())
            return (*it);
        else
            it++;
    }
    return NULL;
}

void GameView::setControlledCreature(Order::t_order const &cr) {
    IND::Creature           *creatureTmp;

    creatureTmp = getCreatureById(*((size_t*)cr.data));
    if (creatureTmp != NULL){
        Controlled = creatureTmp;
    }
    for (auto a = creatures.begin(); a != creatures.end() ; ++a) {
        if ((*a)->getSceneId() == *((size_t*)cr.data)) {
            players.push_back(*a);
            creatures.erase(a);
            break;
        }
    }
    _HUDManager->setControlledCreature(creatureTmp);
}

void GameView::treatAddPartyMember(Order::t_order const &cr) {
    addPartyMember              *member = (addPartyMember*)cr.data;

    _HUDManager->addPartyMember(findCreatureEverywhereById(member->controlledCreatureId), member->name);
    for (auto a = creatures.begin(); a != creatures.end() ; ++a) {
        if ((*a)->getSceneId() == member->controlledCreatureId) {
            players.push_back(*a);
            creatures.erase(a);
            break;
        }
    }
}

bool GameView::isRunning(void) const {
    return _isRunning;
}

void GameView::treatUseSpellOrder(Order::t_order const &cr) {
    useSpell         *spell = (useSpell*)cr.data;
    IND::Creature    *caster = findCreatureEverywhereById(spell->casterId);
    IND::Creature    *target = findCreatureEverywhereById(spell->targetId);

    if (caster && target){
        caster->useSpell((IND::Spell::Type)spell->spellType, target);
    }
}

IND::Creature *GameView::getCreatureByNode(Ogre::SceneNode *node) {
    std::list<IND::Creature*>::iterator   it = creatures.begin();

    if (node) {
        while (it != creatures.end()) {
            if ((*it) != NULL) {
                if ((*it)->getSceneNode() == node)
                    return (*it);
            }
            it++;
        }
    }
    for (auto j = players.begin(); j != players.end(); ++j) {
        if ((*j)->getSceneNode() == node)
            return (*j);
    }
    return NULL;
}

void GameView::treatSetHpMpOrder(Order::t_order const &cr) {
    setHpMp                 *tmp = (setHpMp*)(cr.data);
    IND::Creature           *creatureTmp;

    creatureTmp = findCreatureEverywhereById(tmp->creatureId);

    if (creatureTmp != NULL){
        creatureTmp->setCurrentHp(tmp->currentHp);
        creatureTmp->setCurrentMp(tmp->currentMp);
    }
}

void GameView::treatSetDeadCreatureOrder(Order::t_order const &cr) {
    IND::Creature           *creatureTmp;

    creatureTmp = findCreatureEverywhereById(*(size_t*)((cr.data)));

    if (creatureTmp) {
        creatureTmp->dead();
    }
}

IND::Creature *GameView::getPlayerById(size_t id) {
    std::list<IND::Creature*>::iterator           it = players.begin();
    while (it != players.end()){
        if ((*it) != NULL && id == (*it)->getSceneId())
            return (*it);
        else
            it++;
    }
    return NULL;
}

IND::Creature *GameView::findCreatureEverywhereById(size_t id) {
    IND::Creature       *tmp;
    if ((tmp = getCreatureById(id))){
        return tmp;
    }
    else if ((tmp = getPlayerById(id))){
        return tmp;
    }
    return tmp;
}

void GameView::treatErrorMessageOrder(Order::t_order const &cr) {
    char        *ErrorText = (char*)cr.data;
    std::string message;

    message += "[colour='FFFF0000']";
    message += ErrorText;

    _HUDManager->setErrorMessage(message);
}

void GameView::treatRespawnCreatureOrder(Order::t_order const &cr) {
    RespawnCreature         *tmp = (RespawnCreature*)(cr.data);
    IND::Creature           *creatureTmp;

    creatureTmp = findCreatureEverywhereById(tmp->id);

    if (creatureTmp != NULL){
        creatureTmp->respawnIt(Ogre::Vector3(tmp->x, tmp->y, tmp->z));
    }
}

void GameView::treatSetBuffOnCreatureOrder(Order::t_order const &cr) {
    setBuffOnCreature       *tmp = (setBuffOnCreature*)(cr.data);
    IND::Creature           *currentCreature = findCreatureEverywhereById(tmp->target);
    IND::Buff               *buffTmp;

    if (currentCreature && (buffTmp = IND::ObjectFactory::createBuff(tmp->type)) != NULL)
        currentCreature->addBuff(buffTmp);
}
void GameView::treatAddWorldObjectOrder(Order::t_order const &cr) {
    addWordldObject         *tmp = (addWordldObject*)(cr.data);
    IND::WorldStaticObject  *object;

    object = IND::ObjectFactory::createStaticObject(0, Ogre::Vector3(tmp->x, tmp->y, tmp->z), mSceneMgr);
    if (object){
        staticObjects.push_back(object);
    }
}

IND::Creature *GameView::getTargetCreature(void) {
    return this->targetCreature;
}

IND::Creature *GameView::getControlledCreature(void) {
    return this->Controlled;
}
