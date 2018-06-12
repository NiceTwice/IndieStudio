//
// Created by nicetwice on 31/05/16.
//

#ifndef TESTCEGUI_WALLCUBE_H
#define TESTCEGUI_WALLCUBE_H


#include <WorldStaticObject.h>

namespace IND {
    class WallCube : public WorldStaticObject{
    public:
        WallCube(Ogre::Vector3 const &position, Ogre::Vector3 const &rotation, Ogre::SceneManager *sceneManager);
        ~WallCube();
    };
}

#endif //TESTCEGUI_WALLCUBE_H
