#include "appdata.h"

#include <QIcon>

// Takes an icon and converts it to a 61x61 pixmap
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

// If an icon is un-found, search for it from the compiled-in icons
// TODO: Some icons aren't even searching, like thunderbolt doesn't search
QPixmap searchIcon(QString path, std::string name) {
    std::string search = ":/Resources/" + (std::string)path.toUtf8() + ".png";

    QImage image(search.c_str());
    QImage resized = image.scaled(61, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap pixmap = QPixmap::fromImage(resized);

    if (pixmap.width() != 0) {
        return pixmap;
    }
    else {
        QImage question(":/Resources/question.png");
        resized = question.scaled(61, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        pixmap = QPixmap::fromImage(resized);

        return pixmap;
    }
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
