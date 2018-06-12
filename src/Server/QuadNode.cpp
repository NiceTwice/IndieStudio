#include "QuadNode.hh"

QuadNode::QuadNode(const std::vector<float> &coords, size_t maxComplexity, size_t currentComplexity) :
_coords(coords), _complexity(currentComplexity), _xsize(coords[1] - coords[0]), _ysize(coords[3] - coords[2]) {
	if (currentComplexity < maxComplexity) {
		_children.push_back(new QuadNode(getChildCoords(1), maxComplexity, currentComplexity + 1));
		_children.push_back(new QuadNode(getChildCoords(2), maxComplexity, currentComplexity + 1));
		_children.push_back(new QuadNode(getChildCoords(3), maxComplexity, currentComplexity + 1));
		_children.push_back(new QuadNode(getChildCoords(4), maxComplexity, currentComplexity + 1));
	}
}

QuadNode::~QuadNode() {
}

std::vector<float> &QuadNode::getChildCoords(size_t nChild) const {
	std::vector<float> &coords = *(new std::vector<float>());

	switch (nChild) {
			case 1:
				coords.push_back(_coords[0]);
				coords.push_back((_coords[0] + _coords[1]) / 2);
				coords.push_back(_coords[2]);
				coords.push_back((_coords[2] + _coords[3]) / 2);
				break;
			case 2:
				coords.push_back((_coords[0] + _coords[1]) / 2);
				coords.push_back(_coords[1]);
				coords.push_back(_coords[2]);
				coords.push_back((_coords[2] + _coords[3]) / 2);
				break;
			case 3:
				coords.push_back(_coords[0]);
				coords.push_back((_coords[0] + _coords[1]) / 2);
				coords.push_back((_coords[2] + _coords[3]) / 2);
				coords.push_back(_coords[3]);
				break;
			default:
				coords.push_back((_coords[0] + _coords[1]) / 2);
				coords.push_back(_coords[1]);
				coords.push_back((_coords[2] + _coords[3]) / 2);
				coords.push_back(_coords[3]);
				break;
	}
	return coords;
}

const std::list<Creature *> &QuadNode::getCreatures(void) const {
	return _creatures;
}

const std::list<Wall *> &QuadNode::getWalls(void) const {
	 return _walls;
}

bool QuadNode::isHere(Ogre::Vector3 target) const {
	if ((target.x >= _coords[0]) && (target.x <= _coords[1]) && (target.z >= _coords[2]) && (target.z <= _coords[3]))
		return true;
	return false;
}

QuadNode *QuadNode::getNode(Ogre::Vector3 target) const {
	QuadNode *ret;

	if ((target.x >= _coords[0]) && (target.x <= _coords[1]) && (target.z >= _coords[2]) && (target.z <= _coords[3])) {
		for (std::list<QuadNode *>::const_iterator it = _children.begin(); it != _children.end(); ++it) {
			if ((*it)->_children.size() == 0) {
				if ((*it)->isHere(target) == true) 
					return (*it);
			}
			else
				if ((ret = (*it)->getNode(target)) != nullptr)
					return ret;
		}
	}
	return nullptr;
}

bool QuadNode::pushCreature(Creature *target) {
	if (target == nullptr)
		return false;

	Ogre::Vector3 targetPos = target->getPosition();
	if ((targetPos.x >= _coords[0]) && (targetPos.x <= _coords[1]) && (targetPos.z >= _coords[2]) && (targetPos.z <= _coords[3]))
		{
			if (_children.size() == 0) {
				_creatures.push_back(target);
				return true;
			}
			else
				for (std::list<QuadNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
					if ((*it)->pushCreature(target))
						return true;
				}
			return false;
		}
	return false;
}

bool QuadNode::popCreature(Creature *target) {
	if (target == nullptr)
		return false;

	Ogre::Vector3 targetPos = target->getPosition();
	if (_children.size() == 0) {
		for (std::list<Creature *>::iterator it = _creatures.begin(); it != _creatures.end(); ++it) {
			if ((*it) == target) {
				_creatures.erase(it);
				return true;
			}
		}
	} else {
		for (std::list<QuadNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
			if ((*it)->popCreature(target))
				return true;
		}
	}
	return false;
}

const std::vector<float> &QuadNode::getCoords(void) const {
	return _coords;
}

bool QuadNode::pushWall(Wall *target) {
	if (target == nullptr)
		return false;

	Ogre::Vector3 targetPos = target->getPosition();
	if ((targetPos.x >= _coords[0]) && (targetPos.x <= _coords[1]) && (targetPos.z >= _coords[2]) && (targetPos.z <= _coords[3]))
		{
			if (_children.size() == 0) {
				_walls.push_back(target);
				return true;
			}
			else
				for (std::list<QuadNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
					if ((*it)->pushWall(target))
						return true;
				}
			return false;
		}
	return false;
}

bool QuadNode::popWall(Wall *target) {
	if (target == nullptr)
		return false;

	Ogre::Vector3 targetPos = target->getPosition();
	if (_children.size() == 0) {
		for (std::list<Wall *>::iterator it = _walls.begin(); it != _walls.end(); ++it) {
			if ((*it) == target) {
				_walls.erase(it);
				return true;
			}
		}
	} else {
		for (std::list<QuadNode *>::iterator it = _children.begin(); it != _children.end(); ++it) {
			if ((*it)->popWall(target))
				return true;
		}
	}
	return false;
}
