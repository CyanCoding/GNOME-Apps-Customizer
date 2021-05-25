// Other file includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "create.h"

// Qt includes
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>

// System includes
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cctype>

char *homedir;
std::string desktopFilePath;

void setIcon(QImage image, QLabel *label) {
    QImage resized = image.scaled(41, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap pixmap = QPixmap::fromImage(resized);

    label->setPixmap(pixmap);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Get the user's home directory, like '/home/jason'
    struct passwd *pw = getpwuid(getuid());
    homedir = pw->pw_dir;

    // Set the question mark icon
    QImage questionMarkIcon(":/Resources/question.png");
    setIcon(questionMarkIcon, ui->iconImage);
}

// Gets the file name from the file path
// Input: /home/jason/app.AppImage
// Output: app.AppImage
std::string getFilePath(std::string path) {
    const size_t last_slash_idx = path.find_last_of("\\/");

    if (std::string::npos != last_slash_idx) {
        path = path.erase(0, last_slash_idx + 1);
    }

    return path;
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_locateIcon_clicked() {
    QString selectedIcon = QFileDialog::getOpenFileName(this, "Choose Icon", homedir, "PNG Image (*.png)");

    // Sets the icon box to the icon's file location
    ui->iconBox->setText(selectedIcon);

    if (selectedIcon != "") {
        // Set the app icon
        QImage questionMarkIcon(selectedIcon);
        setIcon(questionMarkIcon, ui->iconImage);
    }
    else {
        // Set the question mark icon
        QImage questionMarkIcon(":/Resources/question.png");
        setIcon(questionMarkIcon, ui->iconImage);
    }


}


void MainWindow::on_locateApp_clicked() {
    QString selectedApp = QFileDialog::getOpenFileName(this, "Choose App", homedir);

    // Sets the icon box to the icon's file location
    ui->appBox->setText(selectedApp);
}


// When the createButton OK button is clicked
void MainWindow::on_createButton_accepted() {
    // Get values from UI elements
    QString name = ui->nameBox->text();
    QString appLocation = ui->appBox->text();
    QString iconLocation = ui->iconBox->text();
    bool terminalSelected = ui->terminalCheckbox->isChecked();

    // Gets the data to write to the .desktop file
    std::string fileContents = getDesktopValues((std::string)appLocation.toUtf8().constData(),
                     (std::string)iconLocation.toUtf8().constData(),
                     (std::string)name.toUtf8().constData(),
                     terminalSelected, homedir);

    // Writes the data to a .desktop file
    writeDesktopFile(fileContents, getDesktopPath((std::string)name.toUtf8().constData(), homedir));
}

