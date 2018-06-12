//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_PROFILE_HH
#define TESTCEGUI_PROFILE_HH

#include <string>

#define PROFILELEN  50

class Profile {
protected:
    std::string _name;
public:
    Profile(std::string const &name);
    virtual ~Profile();

    void setName(std::string const &);

    std::string const &getName() const;
};


#endif //TESTCEGUI_PROFILE_HH
