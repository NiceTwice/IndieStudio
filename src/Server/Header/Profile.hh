//
// Created by debruy_p on 27/04/16.
//

#ifndef SERVER_PROFILE_HH
#define SERVER_PROFILE_HH

#include <string>

# define    NAMELEN     50

# define    PROFILELEN     (NAMELEN)

class Profile {
protected:
    std::string _name;
public:
    Profile();
    virtual ~Profile();

    void setName(std::string const &);

    std::string const &getName() const;

    void *getBuffer() const;
    void loadBuffer(void *);
};


#endif //SERVER_PROFILE_HH
