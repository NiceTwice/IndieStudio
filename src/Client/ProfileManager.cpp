//
// Created by debruy_p on 06/05/16.
//

#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include "ProfileManager.hh"
#include "TutorialApplication.h"
#include "SoundManager.hh"

ProfileManager::ProfileManager():_current(NULL) {
    std::ifstream in;
    std::string dir(PROFILE_DIRECTORY);
    std::string line;
    std::string file(PROFILE_CURRENTFILE);
    try {
        in.open(dir + "/" + file);
        std::getline(in, line);
        loadProfile(line + ".profile");
        in.close();
    }
    catch (std::exception e){
        std::cerr << "Open .profile fail:  " << e.what() << std::endl;
    }
}

ProfileManager::~ProfileManager() {
    std::ofstream out;
    std::string dir(PROFILE_DIRECTORY);
    std::string file(PROFILE_CURRENTFILE);
    errno = 0;
    if (mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0 || errno == EEXIST) {
        try {
            out.open(dir + "/" + file, std::ios::trunc);
            out << _current->getName() << std::endl;
            out.close();
        }
        catch (std::exception &e) {
            std::cerr << "Open .profile fail:  " << e.what() << std::endl;
        }
    }
    else
        std::cerr << "MKDIR fail profile" << std::endl;
    saveProfile();
    delete _current;
}

Profile *ProfileManager::getCurrentProfile() const {
    return _current;
}

bool ProfileManager::loadProfile(std::string const &filename) {
    std::ifstream in;
    std::string dir(PROFILE_DIRECTORY);
    std::string line;
    std::string first;
    std::string second;
    int magic = 0;
    try {
        in.open(dir + "/" + filename);
        in >> magic;
        if (magic == PROFILE_MAGICNBR) {
            if (_current) {
                delete _current;
            }
            _current = new Profile(filename.substr(0, filename.find(".profile")));
            while (!in.eof()) {
                std::getline(in, line);
                if (!line.empty()) {
                    first = line.substr(0, line.find("="));
                    second = line.substr(line.find("=") + 1);
                    if (first.compare("lang") == 0){
                        TutorialApplication::getSingleton().getLanguageManager()->loadLanguage(second + ".lang");
                    }
                    else if (first.compare("mastervolume") == 0){
                        SoundManager::getSingleton().setGeneralVolume(atof(second.c_str()));
                    }
                    else if (first.compare("musicvolume") == 0){
                        SoundManager::getSingleton().setAmbianceVolume(atof(second.c_str()));
                    }
                    else if (first.compare("effectsvolume") == 0){
                        SoundManager::getSingleton().setEffectVolume(atof(second.c_str()));
                    }
                }
            }
        }
        else {
            std::cerr << "LoadProfile: " << filename << ": Bad magic nbr" << std::endl;
            in.close();
            return false;
        }
        in.close();
    }
    catch (std::exception &e){
        std::cerr << "Open .profile fail:  " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool ProfileManager::saveProfile() {
    if (!_current)
        return false;
    std::string dir_path(PROFILE_DIRECTORY);
    errno = 0;
    if (mkdir(dir_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0 || errno == EEXIST) {
        std::ofstream out;
        try {
            out.open(dir_path + "/" + _current->getName() + ".profile", std::ios::trunc);

            out << PROFILE_MAGICNBR << std::endl;
            out << "lang=" << TutorialApplication::getSingleton().getLanguageManager()->getCurrentLanguage() << std::endl;
            out << "mastervolume=" << SoundManager::getSingleton().getGeneralVolume() << std::endl;
            out << "musicvolume=" << SoundManager::getSingleton().getAmbianceVolume() << std::endl;
            out << "effectsvolume=" << SoundManager::getSingleton().getEffectVolume() << std::endl;
            out.close();
        }
        catch (std::exception &e) {
            std::cerr << "Open and write in .profile:  " << e.what() << std::endl;
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

void ProfileManager::removeProfile() {
    if (!_current) {
        std::string file(_current->getName());
        file += ".profile";
        std::remove(file.c_str());
    }
}

void ProfileManager::newProfile(std::string const &name) {
    if (_current)
        delete _current;
    _current = new Profile(name);
}



