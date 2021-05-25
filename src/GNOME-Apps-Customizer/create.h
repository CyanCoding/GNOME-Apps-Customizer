#ifndef CREATE_H
#define CREATE_H

#include <iostream>

// Gets the .desktop file path
std::string getDesktopPath(std::string name, std::string homeDir);

// Creates the content for a .desktop file
std::string getDesktopValues(std::string exec, std::string icon, std::string name, bool isTerminal, std::string homeDir);

// Writes to the .desktop file
void writeDesktopFile(std::string text, std::string path);

#endif // CREATE_H
