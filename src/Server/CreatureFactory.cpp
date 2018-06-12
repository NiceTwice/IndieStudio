//
// Created by debruy_p on 30/05/16.
//

#include <Skeleton.hh>
#include <Warrior.hh>
#include <Archer.hh>
#include <Mage.hh>
#include <Assassin.hh>
#include <Priest.hh>
#include "CreatureFactory.hh"

Creature *CreatureFactory::createCreature(Creature::TYPE type, Ogre::Vector3 const &pos, size_t id) {
    switch (type) {
        case Creature::TYPE::SKELETON :
            return new Skeleton(id, pos);
        case Creature::TYPE::WARRIOR :
            return new Warrior(id, pos);
        case Creature::TYPE::ARCHER :
            return new Archer(id, pos);
        case Creature::TYPE::MAGE :
            return new Mage(id, pos);
        case Creature::TYPE::ASSASSIN :
            return new Assassin(id, pos);
        case Creature::TYPE::PRIEST :
            return new Priest(id, pos);
        default :
            break;
    }
    return NULL;
}