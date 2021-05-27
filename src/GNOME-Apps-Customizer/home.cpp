#include "home.h"

#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

// Searches /usr/share/applications and /home/jason/.local/share/applications
// for .desktop files and returns their paths in a vector<string>
void locateDesktopFiles() {
    // fs::create_directories("usr/share/applications");
    std::vector<std::string> pathVector;

    for(auto& p: fs::recursive_directory_iterator("/usr/share/applications")) {
        pathVector.push_back(p.path());
        std::cout << p.path() << "/n";
    }

}
