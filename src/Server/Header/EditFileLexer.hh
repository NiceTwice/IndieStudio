#ifndef _EDITFILELEXER_HH_
# define _EDITFILELEXER_HH_

# include <string>
# include <vector>
# include <stdlib.h>
# include "Creature.hh"
# include "Wall.hh"

namespace EditFile
{
	#define MAX_PLAYERS 5

	enum State {
		NONE = 0,
		FIRST = 1,
		SECOND = 2,
		THIRD = 4,
	};

	struct Room {
		int _x;
		int _y;
		std::string _path;
		char _state;
	};

	struct Map {
		size_t _length;
		size_t _width;
		size_t _complexity;
		char _state;
	};

	struct Creature {
		int _x;
		int _y;
		size_t _type;
		char _state;
	};

	struct Wall {
		int _x;
		int _y;
		char _state;
	};

	enum Line {
		EMPTY,
		COMMENTARY,
		TAG
	};

}

class EditFileLexer {
public:
	EditFileLexer();
	~EditFileLexer();
	std::vector<std::string> getArgsFromTag(const std::string &tag, size_t nline) const;
	EditFile::Map lexMap(std::vector<std::string> args, size_t nline);
	Creature *lexCreature(std::vector<std::string> args, size_t nline, int relX, int relY, size_t id) const;
	Wall *lexWall(std::vector<std::string> args, size_t nline, int relX, int relY) const;
	EditFile::Room lexRoom(std::vector<std::string> args, size_t nline) const;

private:
	void checkMapArg(std::string arg, size_t nline, EditFile::Map *map) const;
	void checkCreatureArg(std::string arg, size_t nline, EditFile::Creature *creature) const;
	void checkWallArg(std::string arg, size_t nline, EditFile::Wall *wall) const;
	void checkRoomArg(std::string arg, size_t nline, EditFile::Room *room) const;
	bool isDigit(const std::string &arg) const;
	bool isNeg(const std::string &arg) const;
	size_t argToSize(const std::string &arg, size_t nline) const;
	int argToInt(const std::string &arg, size_t nline) const;
	std::string getArg(const std::string &part, size_t nline) const;
	bool _mapLexed;
};

#endif // _EDITFILELEXER_HH_