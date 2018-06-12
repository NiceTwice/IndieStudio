//
// main.cpp for indie_studio in /home/debruy_p/projects/tek2/cpp/cpp_indie_studio/src/Server
//
// Made by Pierre Debruyne
// Login   <debruy_p@epitech.eu>
//
// Started on  Mon Apr 25 22:31:17 2016 Pierre Debruyne
// Last update Fri Jun  3 18:41:21 2016 olivier
//

#include <iostream>
#include <csignal>
#include "Server.hh"
#include "QuadTree.hh"
#include "EditFileParser.hh"
#include "Skeleton.hh"

int main(int ac, char **av)
{
  std::vector<Creature *> creatures;
  std::vector<Wall *> walls;
  EditFile::Map map;

  try {
    EditFileParser parser(av[1]);
    parser.parseFile();
    map = parser.getMap();
    creatures = parser.getCreatures();
    walls = parser.getWalls();

    std::cout << "Map : " << map._length << " " << map._width << " " << map._complexity << std::endl;
    QuadTree tree(map._length, map._width, map._complexity);

    for (std::vector<Creature *>::iterator it = creatures.begin(); it != creatures.end(); ++it) {
      std::cout << "Creature - " << (*it)->getId() << " : " << (*it)->getPosition() << std::endl;
      tree.pushCreature(*it);
    }

    for (std::vector<Wall *>::iterator it = walls.begin(); it != walls.end(); ++it) {
      std::cout << "Wall : " << (*it)->getPosition() << std::endl;
      tree.pushWall(*it);
    }

  } catch (std::ios_base::failure e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
