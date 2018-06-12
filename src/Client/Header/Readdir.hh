//
// Created by remyo on 06/05/16.
//

#ifndef CPP_INDIE_STUDIO_READDIR_HH
#define CPP_INDIE_STUDIO_READDIR_HH


#include <string>
#include <vector>

class Readdir {
public:
    static std::vector<std::string> getAllFile(std::string const &path);
};


#endif //CPP_INDIE_STUDIO_READDIR_HH
