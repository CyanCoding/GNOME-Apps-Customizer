#ifndef APPDATA_H
#define APPDATA_H

#include <QPixmap>

#include <iostream>


class AppData {
public:
    std::string name;
    std::string comment;
    std::string exec;
    std::string iconPath;
    bool isTerminal;

    QPixmap resizedIcon;

    QPixmap returnResizedIcon(QString path);
    bool stringToBool(std::string boolean);
};


#endif // APPDATA_H
