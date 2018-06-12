#ifndef _EDITFILEPARSER_HH_
# define _EDITFILEPARSER_HH_

# include <map>
# include "EditFileLexer.hh"
# include "Server.hh"

class EditFileParser {
public:
	EditFileParser(const std::string &path, int relX = 0, int relY = 0);
	~EditFileParser(void);
	void parseFile(void);
	EditFile::Map getMap(void) const;
	std::vector<Creature *> getCreatures(void) const;
	std::vector<Wall *> getWalls(void) const;

private:
	EditFile::Line whatIsIt(std::string line) const;
	void callLexer(std::vector<std::string> args, size_t nline);
	void parseRoom(std::vector<std::string> args, size_t nline);

	std::ifstream _file;
	std::vector<Creature *> _creatures;
	std::vector<Wall *> _walls;
	EditFile::Map _map;
	EditFileLexer lexer;
	int _relX;
	int _relY;
};

#endif // _EDITFILEPARSER_HH_