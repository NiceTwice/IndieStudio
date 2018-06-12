//
// Created by nicetwice on 25/05/16.
//

#ifndef TESTCEGUI_OBJECTFACTORY_HPP
#define TESTCEGUI_OBJECTFACTORY_HPP

#include <map>
#include <WallCube.h>
#include "Creature.h"
#include "Warrior.h"
#include "BuffSpeedBoostFire.h"
#include "SkeletonArcher.h"
#include "SkeletonMage.h"
#include "SkeletonFighter.h"
#include "BuffSlowBoost.h"
#include "BuffFireDamage.h"
#include "Golem.h"
#include "Malygos.h"
#include "Arthas.h"
#include "ArmureBuff.h"

namespace IND {
class ObjectFactory {
private:
    typedef IND::Creature*(*createCreatureFunc)(Ogre::Vector3 const &,Entity::EntityType, Ogre::SceneManager *, size_t);
    typedef IND::WorldStaticObject*(*createStaticObjectFunc)(Ogre::Vector3 const &,Ogre::SceneManager *);
    typedef IND::Buff*(*createBuffFunc)(void);
    //Creatures
private:
    static IND::WorldStaticObject *createWallCube(Ogre::Vector3 const &pos, Ogre::SceneManager *sm){
        return new WallCube(pos, Ogre::Vector3::ZERO, sm);
    }
private:
    static IND::Creature *createSkeletonWarrior(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new Warrior(pos, type, sm, id);
    }
    static IND::Creature *createSkeletonArcher(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new SkeletonArcher(pos, type, sm, id);
    }
    static IND::Creature *createSkeletonFighter(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new SkeletonFighter(pos, type, sm, id);
    }
    static IND::Creature *createSkeletonMage(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new SkeletonMage(pos, type, sm, id);
    }
    static IND::Creature *createAImob(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new AImob(pos, type, sm, id);
    }
    static IND::Creature *createMalygos(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new Malygos(pos, type, sm, id);
    }
    static IND::Creature *createArthas(Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t id){
        return new Arthas(pos, type, sm, id);
    }
    //Buffs
private:
    static IND::Buff    *createSpeedBoostBuff(void){
        return new BuffSpeedBoostFire();
    }
    static IND::Buff    *createSlowBoostBuff(void){
        return new BuffSlowBoost();
    }
    static IND::Buff    *createFireDamageBuff(void){
        return new BuffFireDamage();
    }
    static IND::Buff    *createArmureBuff(void){
        return new ArmureBuff();
    }
private:
    static const std::map<size_t, createCreatureFunc>       createCreatureMap(){
        std::map<size_t, createCreatureFunc> map;
        map[0] = createSkeletonWarrior;
        map[1] = createSkeletonWarrior;
        map[2] = createSkeletonArcher;
        map[3] = createSkeletonMage;
        map[4] = createSkeletonFighter;
        map[5] = createSkeletonWarrior;
        map[6] = createAImob;
        map[7] = createMalygos;
        map[8] = createArthas;
        return map;
    }
    static const std::map<size_t, createCreatureFunc>       creatureMap;

    static const std::map<size_t, createBuffFunc>           createBuffMap(){
        std::map<size_t, createBuffFunc> map;
        map[0] = createSpeedBoostBuff;
        map[1] = createSlowBoostBuff;
        map[2] = createArmureBuff;
        map[3] = createFireDamageBuff;
        return map;
    }
    static const std::map<size_t, createBuffFunc>           buffMap;
    static const std::map<size_t, createStaticObjectFunc>           createStaticObjectMap(){
        std::map<size_t, createStaticObjectFunc> map;
        map[0] = createWallCube;
        return map;
    }
    static const std::map<size_t, createStaticObjectFunc>       staticObjectMap;
public:
    static const std::string                                RED;
    static const std::string                                GREEN;
    static const std::string                                BLUE;
    static const std::string                                WHITE;

    static IND::Creature    *createCreature(size_t id, Ogre::Vector3 const &pos, Entity::EntityType type, Ogre::SceneManager *sm, size_t creatureId){
        std::map<size_t, createCreatureFunc>::const_iterator   it = ObjectFactory::creatureMap.begin();

        while (it != ObjectFactory::creatureMap.end()) {
                if ((*it).first == id){
                    return ((*it).second)(pos, type, sm, creatureId);
                }
            it++;
        }
        return NULL;
    }
    static IND::Buff    *createBuff(size_t id){
        std::map<size_t, createBuffFunc>::const_iterator   it = ObjectFactory::buffMap.begin();

        while (it != ObjectFactory::buffMap.end()) {
                if ((*it).first == id){
                    return ((*it).second)();
                }
            it++;
        }
        return NULL;
    }
    static IND::WorldStaticObject    *createStaticObject(size_t id, Ogre::Vector3 const &pos, Ogre::SceneManager *sm){
        std::map<size_t, createStaticObjectFunc>::const_iterator   it = ObjectFactory::staticObjectMap.begin();

        while (it != ObjectFactory::staticObjectMap.end()) {
                if ((*it).first == id){
                    return ((*it).second)(pos, sm);
                }
            it++;
        }
        return NULL;
    }
};
}

#endif //TESTCEGUI_OBJECTFACTORY_HPP
