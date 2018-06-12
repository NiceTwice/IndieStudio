#include <exception>
#include <sstream>
#include <iostream>
#include "EditFileLexer.hh"
#include "CreatureFactory.hh"

EditFileLexer::EditFileLexer() :
	_mapLexed(false) {
}

EditFileLexer::~EditFileLexer() {
}

std::string EditFileLexer::getArg(const std::string &part, size_t nline) const {
	std::stringstream ss(part);
	std::string arg;

	ss >> arg;
	while (ss >> arg)
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + part + "\" ");
	return arg;
}

std::vector<std::string> EditFileLexer::getArgsFromTag(const std::string &tag, size_t nline) const {
	std::stringstream ss(tag);
	std::vector<std::string> args;
	std::string part;

	while (getline(ss, part, ','))
		args.push_back(getArg(part, nline));
	return args;
}

bool EditFileLexer::isDigit(const std::string &arg) const {
	size_t i = 0;

	if (arg[i] == '-')
		i++;
	while (arg[i])
		if (!isdigit(arg[i++]))
			return false;
	return true;
}

bool EditFileLexer::isNeg(const std::string &arg) const {
	if (arg[0] == '-')
		return true;
	return false;
}

size_t EditFileLexer::argToSize(const std::string &arg, size_t nline) const {
	size_t ret;

	if (!isDigit(arg) || isNeg(arg))
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	try {
		ret = std::stoul(arg);
		return ret;
	} catch (std::invalid_argument e) {
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	} catch (std::out_of_range e) {
		throw std::ios_base::failure("Arg out of range from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	}
}

int EditFileLexer::argToInt(const std::string &arg, size_t nline) const {
	int ret;

	if (!isDigit(arg))
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	try {
		ret = std::stoi(arg);
		return ret;
	} catch (std::invalid_argument e) {
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	} catch (std::out_of_range e) {
		throw std::ios_base::failure("Arg out of range from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	}
}

void EditFileLexer::checkMapArg(std::string arg, size_t nline, EditFile::Map *map) const {
	std::stringstream ss(arg);
	std::string att;
	std::string val;

	getline(ss, att, '=');
	getline(ss, val, '=');
	if (att == "length") {
		if ((map->_state & EditFile::State::FIRST))
			throw std::ios_base::failure("Map attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		map->_state |= EditFile::State::FIRST;
		map->_length = argToSize(val, nline);
	} else if (att == "width") {
		if ((map->_state & EditFile::State::SECOND))
			throw std::ios_base::failure("Map attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		map->_width = argToSize(val, nline);
		map->_state |= EditFile::State::SECOND;
	} else if (att == "complexity") {
		if ((map->_state & EditFile::State::THIRD))
			throw std::ios_base::failure("Map attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		map->_complexity = argToSize(val, nline);
		map->_state |= EditFile::State::THIRD;
	} else {
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	}
	while (getline(ss, att, '='))
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
}

void EditFileLexer::checkCreatureArg(std::string arg, size_t nline, EditFile::Creature *creature) const {
	std::stringstream ss(arg);
	std::string att;
	std::string val;

	getline(ss, att, '=');
	getline(ss, val, '=');
	if (att == "x") {
		if ((creature->_state & EditFile::State::FIRST))
			throw std::ios_base::failure("Creature attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		creature->_x = argToInt(val, nline);
		creature->_state |= EditFile::State::FIRST;
	} else if (att == "y") {
		if ((creature->_state & EditFile::State::SECOND))
			throw std::ios_base::failure("Creature attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		creature->_y = argToInt(val, nline);
		creature->_state |= EditFile::State::SECOND;
	} else if (att == "type") {
		if ((creature->_state & EditFile::State::THIRD))
			throw std::ios_base::failure("Creature attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		creature->_type = argToSize(val, nline);
		creature->_state |= EditFile::State::THIRD;
	} else {
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	}
	while (getline(ss, att, '='))
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
}

void EditFileLexer::checkWallArg(std::string arg, size_t nline, EditFile::Wall *wall) const {
	std::stringstream ss(arg);
	std::string att;
	std::string val;

	getline(ss, att, '=');
	getline(ss, val, '=');
	if (att == "x") {
		if ((wall->_state & EditFile::State::FIRST))
			throw std::ios_base::failure("Wall attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		wall->_x = argToInt(val, nline);
		wall->_state |= EditFile::State::FIRST;
	} else if (att == "y") {
		if ((wall->_state & EditFile::State::SECOND))
			throw std::ios_base::failure("Wall attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		wall->_y = argToInt(val, nline);
		wall->_state |= (int)EditFile::State::SECOND;
	} else {
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	}
	while (getline(ss, att, '='))
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
}

void EditFileLexer::checkRoomArg(std::string arg, size_t nline, EditFile::Room *room) const {
	std::stringstream ss(arg);
	std::string att;
	std::string val;

	getline(ss, att, '=');
	getline(ss, val, '=');
	if (att == "x") {
		if ((room->_state & EditFile::State::FIRST))
			throw std::ios_base::failure("Room attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		room->_x = argToInt(val, nline);
		room->_state |= EditFile::State::FIRST;
	} else if (att == "y") {
		if ((room->_state & EditFile::State::SECOND))
			throw std::ios_base::failure("Room attribute redefined from line " + std::to_string(nline) + " - \"" + att + "\" ");
		room->_y = argToInt(val, nline);
		room->_state |= (int)EditFile::State::SECOND;
	} else {
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
	}
	while (getline(ss, att, '='))
		throw std::ios_base::failure("Syntax Error from line " + std::to_string(nline) + " - \"" + arg + "\" ");
}


EditFile::Map EditFileLexer::lexMap(std::vector<std::string> args, size_t nline) {
	EditFile::Map map;
	std::vector<std::string>::iterator it;

	if (_mapLexed == true)
		throw std::ios_base::failure("Map redefined from line " + std::to_string(nline) + " ");
	map._length = 0;
	map._width = 0;
	map._complexity = 0;
	map._state = EditFile::State::NONE;
	for (it = args.begin() + 1; it != args.end(); ++it) {
		checkMapArg(*it, nline, &map);
	}
	if (map._state != (EditFile::State::FIRST | EditFile::State::SECOND | EditFile::State::THIRD))
		throw std::ios_base::failure("Missing arg from line " + std::to_string(nline) + " - \"MAP need length, width, complexity\" ");
	_mapLexed = true;
	return map;
}

Creature *EditFileLexer::lexCreature(std::vector<std::string> args, size_t nline, int relX, int relY, size_t id) const {
	EditFile::Creature creature;
	Creature *ret;
	std::vector<std::string>::iterator it;

	creature._x = 0;
	creature._y = 0;
	creature._type = 0;
	creature._state = EditFile::State::NONE;
	for (it = args.begin() + 1; it != args.end(); ++it) {
		checkCreatureArg(*it, nline, &creature);
	}
	if (creature._state != (EditFile::State::FIRST | EditFile::State::SECOND | EditFile::State::THIRD))
		throw std::ios_base::failure("Missing arg from line " + std::to_string(nline) + " - \"CREATURE need x, y, type\" ");
	ret = CreatureFactory::createCreature((Creature::TYPE)creature._type, Ogre::Vector3(relX + creature._x, 0, relY + creature._y), id);
	return ret;
}

Wall *EditFileLexer::lexWall(std::vector<std::string> args, size_t nline, int relX, int relY) const {
	EditFile::Wall wall;
	Wall *ret;
	std::vector<std::string>::iterator it;

	wall._x = 0;
	wall._y = 0;
	wall._state = EditFile::State::NONE;
	for (it = args.begin() + 1; it != args.end(); ++it) {
		checkWallArg(*it, nline, &wall);
	}
	if (wall._state != (EditFile::State::FIRST | EditFile::State::SECOND))
		throw std::ios_base::failure("Missing arg from line " + std::to_string(nline) + " - \"WALL need x, y\" ");
	ret = new Wall(Ogre::Vector3(relX + wall._x, 0, relY + wall._y));
	return ret;
}

EditFile::Room EditFileLexer::lexRoom(std::vector<std::string> args, size_t nline) const {
	EditFile::Room room;
	std::vector<std::string>::iterator it;

	room._x = 0;
	room._y = 0;
	room._path = args[0];
	room._state = EditFile::State::NONE;
	for (it = args.begin() + 1; it != args.end(); ++it) {
		checkRoomArg(*it, nline, &room);
	}
	if (room._state != (EditFile::State::FIRST | EditFile::State::SECOND))
		throw std::ios_base::failure("Missing arg from line " + std::to_string(nline) + " - \"ROOM need x, y\" ");
	return room;
}