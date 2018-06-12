#ifndef QUADTREE_HH
# define QUADTREE_HH

# include "QuadNode.hh"

class QuadTree
{
public:
	QuadTree(size_t length, size_t width, size_t complexity = 1);
	~QuadTree();
	std::pair<std::list<Creature *>, std::list<Wall *> > getCollableObjects(Creature *target) const;
	QuadNode *getNode(Ogre::Vector3 target) const;
	void updateCreature(Creature *target);
	void pushCreature(Creature *target);
	void popCreature(Creature *target);
	void pushWall(Wall *target);
	void popWall(Wall *target);

private:
	void addCreatures(Creature *target, const std::list<Creature *> &src, std::list<Creature *> &dest) const;
	void addWalls(const std::list<Wall *> &src, std::list<Wall *> &dest) const;
	QuadNode &_root;
	size_t _length;
	size_t _width;
};

#endif // QUADTREE_HH