#ifndef CREATE_H
#define CREATE_H

#include <QPixmap>
#include <QImage>

#include <iostream>

// Gets the .desktop file path
std::string getDesktopPath(std::string name, std::string homeDir);

// Creates the content for a .desktop file
std::string getDesktopValues(std::string exec, std::string icon, std::string name, bool isTerminal, std::string homeDir);

// Writes to the .desktop file
void writeDesktopFile(std::string text, std::string path);

// Creates a resized useable Pixmap from a QImage
QPixmap getResizedPixmap(QImage image);

#endif // CREATE_H
