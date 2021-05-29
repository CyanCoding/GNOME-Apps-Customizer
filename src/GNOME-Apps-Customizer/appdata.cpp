#include "appdata.h"

#include <QIcon>
#include <QSvgRenderer>
#include <QPainter>

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
    std::string search = ":/Resources/app-icons/" + (std::string)path.toUtf8() + ".png";
    std::string search2 = ":/Resources/app-icons/" + (std::string)path.toUtf8() + ".svg";

    // Search for a .png
    QImage image(search.c_str());
    QImage resized = image.scaled(61, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap pixmap = QPixmap::fromImage(resized);

    if (pixmap.width() != 0) {
        return pixmap;
    }
    else {
        // Search for a .svg instead
        QSvgRenderer renderer = QString(search2.c_str());
        // QSvgRenderer renderer = QString("://Resources/app-icons/androidstudio.svg");
        QImage svgImage(61, 61, QImage::Format_ARGB32);
        //TODO: Images look grainy

        QPainter painter(&svgImage);
        renderer.render(&painter);

        pixmap = QPixmap::fromImage(svgImage);

        if (pixmap.width() != 0) {
            return pixmap;
        }
        else {
            // Last resort, put a question mark icon
            QImage question(":/Resources/question.png");
            resized = question.scaled(61, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            pixmap = QPixmap::fromImage(resized);

            return pixmap;
        }
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
