//
// Created by debruy_p on 08/05/16.
//

#ifndef TESTCEGUI_LANGUAGEMANAGER_HH
#define TESTCEGUI_LANGUAGEMANAGER_HH

#include <string>
#include <map>

#define    LANGUAGE_MAGICNBR     0x9684
#define    LANGUAGE_DIRECTORY    "lang"

class LanguageManager {
protected:
    std::string _currentFile;
    std::map<std::string, std::string> _default;
    std::map<std::string, std::string> _current;
    std::string _notFound;
public:
    LanguageManager();
    virtual ~LanguageManager();

    std::string const &getString(std::string const &id) const;
    std::string const &getCurrentLanguage() const;

    bool loadLanguage(std::string const& filename);

    bool generateLanguageFile(std::string const &path) const;
};


#endif //TESTCEGUI_LANGUAGEMANAGER_HH
