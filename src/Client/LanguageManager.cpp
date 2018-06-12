//
// Created by debruy_p on 08/05/16.
//

#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include "LanguageManager.hh"

LanguageManager::LanguageManager():_currentFile("English"), _default(), _current(), _notFound("OoOoOStringNotFoundOoOoO") {
    _default.insert(std::pair<std::string, std::string>("CreateGame", "Create Game"));
    _default.insert(std::pair<std::string, std::string>("JoinGame", "Join Game"));
    _default.insert(std::pair<std::string, std::string>("Options", "Options"));
    _default.insert(std::pair<std::string, std::string>("Profile", "Profile"));
    _default.insert(std::pair<std::string, std::string>("Quit", "Quit"));
    _default.insert(std::pair<std::string, std::string>("EnterServerIP", "Server Ip:"));
    _default.insert(std::pair<std::string, std::string>("EnterPort", "Port:"));
    _default.insert(std::pair<std::string, std::string>("EnterPassword", "Server password (if it's required):"));
    _default.insert(std::pair<std::string, std::string>("Connect", "Connect"));
    _default.insert(std::pair<std::string, std::string>("Back", "Back"));
    _default.insert(std::pair<std::string, std::string>("Graphism", "Graphism"));
    _default.insert(std::pair<std::string, std::string>("Sound", "Sound"));
    _default.insert(std::pair<std::string, std::string>("Controls", "Controls"));
    _default.insert(std::pair<std::string, std::string>("Language", "Language"));
    _default.insert(std::pair<std::string, std::string>("New", "New"));
    _default.insert(std::pair<std::string, std::string>("Edit", "Edit"));
    _default.insert(std::pair<std::string, std::string>("Delete", "Delete"));
    _default.insert(std::pair<std::string, std::string>("EnterProfilName", "Enter new profile's name:"));
    _default.insert(std::pair<std::string, std::string>("Create", "Create"));
    _default.insert(std::pair<std::string, std::string>("Save", "Save"));
    _default.insert(std::pair<std::string, std::string>("LanguageError", "File language seems corrupted..."));
    _default.insert(std::pair<std::string, std::string>("Welcome", "Welcome back"));
    _default.insert(std::pair<std::string, std::string>("ProfileError", "File profile seems corrupted..."));
    _default.insert(std::pair<std::string, std::string>("PortError", "Wrong server port!"));
    _default.insert(std::pair<std::string, std::string>("Send", "Send"));
    _default.insert(std::pair<std::string, std::string>("StartGame", "Start Game"));
    _default.insert(std::pair<std::string, std::string>("MasterVolume", "Master volume"));
    _default.insert(std::pair<std::string, std::string>("MusicVolume", "Music volume"));
    _default.insert(std::pair<std::string, std::string>("EffectsVolume", "Effects volume"));
    _default.insert(std::pair<std::string, std::string>("Skeleton", "Skeleton"));
    _default.insert(std::pair<std::string, std::string>("Warrior", "Warrior"));
    _default.insert(std::pair<std::string, std::string>("BowMan", "BowMan"));
    _default.insert(std::pair<std::string, std::string>("Mage", "Mage"));
    _default.insert(std::pair<std::string, std::string>("Assassin", "Assassin"));
    _default.insert(std::pair<std::string, std::string>("Priest", "Priest"));
}

LanguageManager::~LanguageManager() {

}

std::string const &LanguageManager::getString(std::string const &id) const {
    auto it = _current.find(id);
    if (it != _current.end()){
        return ((*it).second);
    }
    it = _default.find(id);
    if (it != _default.end()){
        return ((*it).second);
    }
    return (_notFound);
}

bool LanguageManager::generateLanguageFile(const std::string &filename) const {
    std::string dir_path(LANGUAGE_DIRECTORY);
    errno = 0;
    if (mkdir(dir_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0 || errno == EEXIST) {
        std::ofstream out;
        try {
            out.open(dir_path + "/" + filename + ".lang", std::ios::trunc);

            out << LANGUAGE_MAGICNBR << std::endl;
            for (auto it = _default.begin(); it != _default.end() ; ++it) {
                out << (*it).first << "=" << (*it).second << std::endl;
            }
            out.close();
        }
        catch (std::exception &e) {
            std::cerr << "Open and write in .lang:  " << e.what() << std::endl;
            out.close();
            return false;
        }
    }
    else {
        std::cerr << "MKDIR fail." << std::endl;
        return false;
    }
    return true;
}

bool LanguageManager::loadLanguage(std::string const &filename) {

    std::ifstream in;
    std::string dir(LANGUAGE_DIRECTORY);
    std::string line;
    std::string first;
    std::string second;
    int magic = 0;
    try {
        in.open(dir + "/" + filename);
        in >> magic;
        if (magic == LANGUAGE_MAGICNBR) {
            _current.clear();
            while (!in.eof()) {
                std::getline(in, line);
                if (!line.empty()) {
                    first = line.substr(0, line.find("="));
                    second = line.substr(line.find("=") + 1);
                    _current.insert(std::pair<std::string, std::string>(first, second));
                }
            }
        }
        else {
            std::cerr << "LoadLanguage: " << filename << ": Bad magic nbr" << std::endl;
            in.close();
            return false;
        }
        in.close();
    }
    catch (std::exception &e){
        std::cerr << "Open .lang fail:  " << e.what() << std::endl;
        return false;
    }
    _currentFile = filename.substr(0, filename.find(".lang"));
    return true;
}

std::string const &LanguageManager::getCurrentLanguage() const {
    return _currentFile;
}