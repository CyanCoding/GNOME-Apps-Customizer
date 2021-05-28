#include "appdata.h"

// Takes the path of a .png file and converts it to a proper-sized pixmap
QPixmap AppData::returnResizedIcon(QString path) {
    QImage image(path);

    QImage resized = image.scaled(41, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap pixmap = QPixmap::fromImage(resized);

    return pixmap;
}

// Takes an input of 'false' or 'true' and returns true/false
bool AppData::stringToBool(std::string boolean) {
    if (boolean == "true") {
        return true;
    }
    else {
        return false;
    }
}
