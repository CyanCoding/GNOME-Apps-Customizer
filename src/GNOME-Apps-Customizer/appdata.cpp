#include "appdata.h"

#include <QIcon>

QPixmap AppData::returnResizedIcon_icon(QIcon icon) {
    QPixmap pixmap = icon.pixmap(icon.actualSize(QSize(61, 61)));

    return pixmap;
}

// Takes the path of a .png file and converts it to a proper-sized pixmap
QPixmap AppData::returnResizedIcon_string(QString path) {
    QImage image(path);

    QImage resized = image.scaled(61, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);

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
