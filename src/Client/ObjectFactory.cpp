//
// Created by nicetwice on 25/05/16.
//

#include "ObjectFactory.hpp"


const std::map<size_t, IND::ObjectFactory::createCreatureFunc> IND::ObjectFactory::creatureMap = IND::ObjectFactory::createCreatureMap();
const std::map<size_t, IND::ObjectFactory::createBuffFunc> IND::ObjectFactory::buffMap = IND::ObjectFactory::createBuffMap();
const std::map<size_t, IND::ObjectFactory::createStaticObjectFunc > IND::ObjectFactory::staticObjectMap = IND::ObjectFactory::createStaticObjectMap();
const std::string IND::ObjectFactory::RED = "[colour='FFFF0000']";
const std::string IND::ObjectFactory::GREEN = "[colour='FF00FF00']";
const std::string IND::ObjectFactory::BLUE = "[colour='FF0000FF']";
const std::string IND::ObjectFactory::WHITE = "[colour='FFFFFFFF']";
