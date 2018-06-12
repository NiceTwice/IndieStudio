#ifndef QUADNODE_HH_
# define QUADNODE_HH_

# include <vector>
# include <list>
# include "Creature.hh"
# include "Wall.hh"

class QuadNode
{
public:
	QuadNode(const std::vector<float> &coords, size_t maxComplexity, size_t currentComplexity = 1);
	~QuadNode();
	const std::list<Creature *> &getCreatures(void) const;
	const std::list<Wall *> &getWalls(void) const;
	QuadNode *getNode(Ogre::Vector3 target) const;
	bool pushCreature(Creature *target);
	bool popCreature(Creature *target);
	bool pushWall(Wall *target);
	bool popWall(Wall *target);
	const std::vector<float> &getCoords(void) const;

private:
	std::vector<float> &getChildCoords(size_t nChild) const;
	bool isHere(Ogre::Vector3 target) const;
	size_t _complexity;
	std::list<QuadNode *> _children;
	std::list<Creature *> _creatures;
	std::list<Wall *> _walls;
	/* Repésente les coordonnées points qui délimitent la zone
	** _coords[0] = Xmin
	** _coords[1] = Xmax
	** _coords[2] = Ymin
	** _coords[3] = Ymax
	*/
	std::vector<float> _coords;
	size_t _xsize;
	size_t _ysize;
};

#endif // QUADNODE_HH_