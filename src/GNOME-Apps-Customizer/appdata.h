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

    QPixmap returnResizedIcon_icon(QIcon icon);
    QPixmap returnResizedIcon_string(QString path);
    QPixmap searchIcon(QString path);
    bool stringToBool(std::string boolean);
};


#endif // APPDATA_H
