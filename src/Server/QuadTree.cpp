#include <stdexcept>
#include "QuadTree.hh"

static QuadNode &initRoot(size_t length, size_t width, size_t complexity) {
	std::vector<float> coords;

	float f = -0.1;
	coords.push_back((-1.0) * (length / 2));
	coords.push_back(length / 2);
	coords.push_back((-1.0) * (width / 2));
	coords.push_back(width / 2);
	QuadNode &root = *(new QuadNode(coords, complexity, 0));
	return root;
}

QuadTree::QuadTree(size_t length, size_t width, size_t complexity) :
	_root(initRoot(length, width, complexity)), _length(length), _width(width) {
}

QuadTree::~QuadTree() {
}

void QuadTree::addCreatures(Creature *target, const std::list<Creature *> &src, std::list<Creature *> &dest) const {
	bool f;

	for (std::list<Creature *>::const_iterator it = src.begin(); it != src.end(); ++it) {
		f = false;
		if (*it != target) {
			for (std::list<Creature *>::const_iterator it2 = dest.begin(); it2 != dest.end(); ++it2) {
				if ((*it) == (*it2)) {
					f = true;
					break;
				}
			}
			if (f == false)
				dest.push_back(*it);
		}
	}
}

void QuadTree::addWalls(const std::list<Wall *> &src, std::list<Wall *> &dest) const {
	bool f;

	for (std::list<Wall *>::const_iterator it = src.begin(); it != src.end(); ++it) {
		f = false;
		for (std::list<Wall *>::const_iterator it2 = dest.begin(); it2 != dest.end(); ++it2) {
			if ((*it) == (*it2)) {
				f = true;
				break;
			}
		}
		if (f == false)
			dest.push_back(*it);
	}
}

std::pair<std::list<Creature *>, std::list<Wall *> > QuadTree::getCollableObjects(Creature *target) const {
	Ogre::Vector3 targetPos = target->getPosition();
	QuadNode *node = _root.getNode(targetPos);
	QuadNode *tmp;
	std::list<Creature *> creatures;
	std::list<Wall *> walls;
	Ogre::Vector3 targetTmp;
	std::pair<std::list<Creature *>, std::list<Wall *> > ret;

	addCreatures(target, node->getCreatures(), *(&creatures));
	addWalls(node->getWalls(), *(&walls));

	// The right border
	targetTmp = targetPos;
	targetTmp.x += 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The left border
	targetTmp = targetPos;
	targetTmp.x -= 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The top border
	targetTmp = targetPos;
	targetTmp.z += 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The bottom border
	targetTmp = targetPos;
	targetTmp.z -= 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The right-bottom corner
	targetTmp = targetPos;
	targetTmp.x += 200;
	targetTmp.z -= 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The left-bottom corner
	targetTmp = targetPos;
	targetTmp.x -= 200;
	targetTmp.z -= 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The right-top corner
	targetTmp = targetPos;
	targetTmp.x += 200;
	targetTmp.z += 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	// The left-top corner
	targetTmp = targetPos;
	targetTmp.x -= 200;
	targetTmp.z += 200;
	tmp = getNode(targetTmp);
	if (tmp != node && tmp) {
		addCreatures(target, tmp->getCreatures(), *(&creatures));
		addWalls(tmp->getWalls(), *(&walls));
	}

	ret.first = creatures;
	ret.second = walls;
	return ret;
}

QuadNode *QuadTree::getNode(Ogre::Vector3 target) const {
	return _root.getNode(target);
}

void QuadTree::updateCreature(Creature *target) {
	if (target == nullptr)
		throw std::logic_error("Error update a null creature\n");
	popCreature(target);
	pushCreature(target);
}

void QuadTree::pushCreature(Creature *target) {
	if (_root.pushCreature(target) == false)
		throw std::logic_error("Error when push Creature to x=" + std::to_string(target->getPosition().x) + " and y=" + std::to_string(target->getPosition().y) + "\n");
}

void QuadTree::popCreature(Creature *target) {
	if (_root.popCreature(target) == false)
		throw std::logic_error("Error when pop Creature to x=" + std::to_string(target->getPosition().x) + " and y=" + std::to_string(target->getPosition().y) + "\n");
}

void QuadTree::pushWall(Wall *target) {
	if (_root.pushWall(target) == false)
		throw std::logic_error("Error when push Wall to x=" + std::to_string(target->getPosition().x) + " and y=" + std::to_string(target->getPosition().y) + "\n");
}

void QuadTree::popWall(Wall *target) {
	if (_root.popWall(target) == false)
		throw std::logic_error("Error when pop Wall to x=" + std::to_string(target->getPosition().x) + " and y=" + std::to_string(target->getPosition().y) + "\n");
}
