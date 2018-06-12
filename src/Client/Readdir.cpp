//
// Created by remyo on 06/05/16.
//

#include <sys/types.h>
#include <dirent.h>
#include <stdexcept>
#include "Readdir.hh"

std::vector<std::string> Readdir::getAllFile(std::string const &path) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *dirent;

    if (!(dir = opendir(path.c_str())))
        throw std::runtime_error("Failed to open " + path);
    while (dirent = readdir(dir)) {
        if (std::string("..").compare(dirent->d_name) != 0 && std::string(".").compare(dirent->d_name) != 0)
            files.push_back(dirent->d_name);
    }
    return files;
}

