#include "home.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Returns true if a file path ends in .desktop
bool verifyDesktopFile(std::string filePath) {
    if (filePath.substr(filePath.find_last_of(".") + 1) == "desktop") {
        return true;
    }
    return false;
}

// Searches /usr/share/applications and /home/jason/.local/share/applications
// for .desktop files and returns their paths in a vector<string>
std::vector<std::string> locateDesktopFiles(std::string homeDir) {
    // fs::create_directories("usr/share/applications");
    std::vector<std::string> pathVector;

    for(auto& p: fs::recursive_directory_iterator("/usr/share/applications")) {
        if (verifyDesktopFile(p.path())) { // Check to make sure we're only reporting .desktop files
            pathVector.push_back(p.path());
            std::cout << p.path() << std::endl;
        }
    }

    for(auto& p: fs::recursive_directory_iterator(homeDir + "/.local/share/applications")) {
        if (verifyDesktopFile(p.path())) {
            pathVector.push_back(p.path());
        }
    }

    return pathVector;
}

// This returns a dictionary of .desktop results
std::map<std::string, std::string> getDesktopFileDetails(std::string path) {
    // Read text from file
    std::ifstream file(path);
    std::string fileDetails;
    while (std::getline(file, fileDetails)) {
        // Loops for every line and writes it to the string
    }
    file.close();

    dictionary* ini = iniparser_load(path.c_str());
    std::map<std::string, std::string> dictionary;

    if (ini == NULL) {
        std::cout << "Cannot parse file: " << path << std::endl;
        return dictionary;
    }

    const char* results = iniparser_getstring(ini, "Desktop Entry:Name", "NULL");
    dictionary["Name"] = results;

    results = iniparser_getstring(ini, "Desktop Entry:Comment", "NULL");
    dictionary["Comment"] = results;

    results = iniparser_getstring(ini, "Desktop Entry:Exec", "NULL");
    dictionary["Exec"] = results;

    results = iniparser_getstring(ini, "Desktop Entry:Icon", "NULL");
    dictionary["Icon"] = results;

    bool boolResults = iniparser_getboolean(ini, "Desktop Entry:Terminal", 0);
    if (boolResults) {
        results = "true";
    }
    else {
        results = "false";
    }
    dictionary["Terminal"] = results;

    dictionary["Path"] = path;

    iniparser_freedict(ini);

    return dictionary;
}
