#include "create.h"

#include <fstream>


// Gets the .desktop file path
std::string getDesktopPath(std::string name, std::string homeDir) {
    return homeDir + "/.local/share/applications/" + name + ".desktop";
}


// Creates the content for a .desktop file
std::string getDesktopValues(std::string exec, std::string icon, std::string name, bool isTerminal, std::string homeDir) {
    std::string fileContents = "";

    std::string terminal = "false";

    if (isTerminal) {
        terminal = "true";
    }

    /*
     * This is the correct form for a .desktop file:
     *
     * [Desktop Entry]
     * Type=Application
     * Encoding=UTF-8
     * Name=AppAdder
     * Exec=/home/jason/app.AppImage
     * Icon=/home/jason/Pictures/app.png
     * Terminal=false
     * Actions=Remove;
     *
     * [Desktop Action Remove]
     * Exec=rm /home/jason/.local/share/applications/AppAdder.desktop
     */

    fileContents += "[Desktop Entry]\n";
    fileContents += "Type=Application\n";
    fileContents += "Encoding=UTF-8\n";
    fileContents += "Name=" + name + "\n"; // Name=AppAdder
    // fileContents += "Comment=A simple program\n";
    fileContents += "Exec=" + exec + "\n";
    fileContents += "Icon=" + icon + "\n";
    fileContents += "Terminal=" + terminal + "\n"; // Terminal=false
    fileContents += "Actions=Remove;\n";

    fileContents += "\n[Desktop Action Remove]\n";
    fileContents += "Name=Uninstall app from system\n";

    fileContents += "Exec=rm " + getDesktopPath(name, homeDir) + "\n";

    return fileContents;
}


// Writes to the .desktop file
void writeDesktopFile(std::string text, std::string path) {
    std::ofstream file(path);

    file << text;

    file.close();
}
