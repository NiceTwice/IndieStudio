//
// Created by nicetwice on 31/05/16.
//

#ifndef TESTCEGUI_WORLDSTATICOBJECT_H
#define TESTCEGUI_WORLDSTATICOBJECT_H

#include <Entity.h>

namespace IND {
    class WorldStaticObject : public Entity{
    protected:
        Ogre::Vector3           position;
        Ogre::Vector3           rotation;
        std::string             _meshName;
    public:
        ~WorldStaticObject();
    };
}

#endif //TESTCEGUI_WORLDSTATICOBJECT_H
