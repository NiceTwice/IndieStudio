//
// Created by zibaire on 03/06/16.
//

#ifndef CPP_INDIE_STUDIO_TREECUBE_H
#define CPP_INDIE_STUDIO_TREECUBE_H

#include <WorldStaticObject.h>

namespace IND {
    class TreeCube : public WorldStaticObject{
    public:
        TreeCube(Ogre::Vector3 const &position, Ogre::Vector3 const &rotation, Ogre::SceneManager *sceneManager);
        ~TreeCube();
    };
}


#endif //CPP_INDIE_STUDIO_TREECUBE_H
