#include <exception>
#include "EditFileParser.hh"

EditFileParser::EditFileParser(const std::string &path, int relX, int relY) :
	_file(path), _relX(relX), _relY(relY) {
	if (!_file)
		throw std::ios_base::failure(path + " : No such file or directory ");
}

EditFileParser::~EditFileParser(void) {
}

EditFile::Line EditFileParser::whatIsIt(std::string line) const {
	for (int i = 0; i != line.size(); i++) {
		if (line[i] != ' ' && line[i] != '\t')
			if (line[i] == '#') {
				return EditFile::COMMENTARY;
			}
			else {
				return EditFile::TAG;
			}
	}
	return EditFile::EMPTY;
}

void EditFileParser::parseRoom(std::vector<std::string> args, size_t nline) {
	EditFile::Room room = lexer.lexRoom(args, nline);
	EditFileParser parser("maps/" + room._path + ".map", _relX + room._x, _relY + room._y);
	parser.parseFile();
	std::vector<Creature *> creatures = parser.getCreatures();
	std::vector<Wall *> walls = parser.getWalls();
	
	for (std::vector<Creature *>::iterator it = creatures.begin(); it != creatures.end(); ++it) {
		_creatures.push_back(*it);
	}

	for (std::vector<Wall *>::iterator it = walls.begin(); it != walls.end(); ++it) {
		_walls.push_back(*it);
	}
}

void EditFileParser::callLexer(std::vector<std::string> args, size_t nline) {
	if (args[0] == "MAP") {
		_map = lexer.lexMap(args, nline);
	} else if (args[0] == "CREATURE") {
		_creatures.push_back(lexer.lexCreature(args, nline, _relX, _relY, Server::getSingleton().getNextId()));
	} else if (args[0] == "WALL") {
		_walls.push_back(lexer.lexWall(args, nline, _relX, _relY));
	} else {
		parseRoom(args, nline);
	}

}

 void EditFileParser::parseFile(void) {
	std::string line;
	std::vector<std::string> args;
	size_t i = 1;
	
	while (std::getline(_file, line)) {
	    if (whatIsIt(line) == EditFile::TAG) {
	    	args = lexer.getArgsFromTag(line, i);
	    	callLexer(args, i);
	    }
	    i++;
	}
	_file.close();
}

EditFile::Map EditFileParser::getMap(void) const {
	return _map;
}

std::vector<Creature *> EditFileParser::getCreatures(void) const {
	return _creatures;
}

std::vector<Wall *> EditFileParser::getWalls(void) const {
	return _walls;
}
