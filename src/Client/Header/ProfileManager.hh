//
// Created by debruy_p on 06/05/16.
//

#ifndef TESTCEGUI_PROFILEMANAGER_HH
#define TESTCEGUI_PROFILEMANAGER_HH

#include <list>
#include "Profile.hh"

#define    PROFILE_MAGICNBR     0x4586
#define    PROFILE_DIRECTORY    "Profiles"
#define    PROFILE_CURRENTFILE  "current"

class ProfileManager {
protected:
    Profile* _current;
public:
    ProfileManager();
    virtual ~ProfileManager();

    Profile *getCurrentProfile() const;

    void newProfile(std::string const &name);

    bool loadProfile(std::string const &filename);
    bool saveProfile();
    void removeProfile();
};


#endif //TESTCEGUI_PROFILEMANAGER_HH
