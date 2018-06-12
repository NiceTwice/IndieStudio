//
// Created by nicetwice on 08/05/16.
//

#ifndef OGREGAMEPLAY_ENTITY_H
#define OGREGAMEPLAY_ENTITY_H

#include <OGRE/Ogre.h>

size_t          getNextId(void);

namespace IND {
    class Entity {
    public:
        enum EntityType {
            Ally = 0,
            Enemy = 1
        };
    protected:
        IND::Entity::EntityType _type;
        Ogre::Vector3 position;
        Ogre::SceneManager      *_scnMgr;
        Ogre::SceneNode         *mNode;
        Ogre::Entity            *mEntity;
        size_t                  sceneId;
    public:
        virtual ~Entity();
        Ogre::SceneNode  *getSceneNode(void) const;
        Ogre::Entity *getEntity(void) const;
        Ogre::SceneManager *getSceneManager(void) const;
    };
}

#endif //OGREGAMEPLAY_ENTITY_H
