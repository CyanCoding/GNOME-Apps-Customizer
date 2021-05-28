// Other file includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "create.h"
#include "home.h"
#include "appdata.cpp"

// Qt includes
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>
#include <QTreeWidget>
#include <QTreeWidgetItem>

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


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Get the user's home directory, like '/home/jason'
    struct passwd *pw = getpwuid(getuid());
    homedir = pw->pw_dir;

    // Set the question mark icon
    QImage questionMarkIcon(":/Resources/question.png");
    ui->iconImage->setPixmap(getResizedPixmap(questionMarkIcon));

    // Set up the QTreeView
    std::vector<std::string> desktopFiles = locateDesktopFiles(homedir);

    getDesktopFileDetails(desktopFiles[0]);

    for (int i = 0; i < desktopFiles.size(); i++) { // Make a QTreeWidgetItem for each desktop file
        QTreeWidgetItem *item = new QTreeWidgetItem();
        try {
            std::map<std::string, std::string> dictionary = getDesktopFileDetails(desktopFiles[i]);

            if (dictionary.empty()) {
                continue;
            }

            item->setText(0, dictionary.find("Name")->second.c_str());

            // Fill in the class values
            AppData data;
            data.name = dictionary.find("Name")->second;
            data.comment = dictionary.find("Comment")->second;
            data.exec = dictionary.find("Exec")->second;
            data.iconPath = dictionary.find("Icon")->second;
            data.isTerminal = data.stringToBool(dictionary.find("Terminal")->second);
            data.resizedIcon = data.returnResizedIcon(dictionary.find("Icon")->second.c_str());

            ui->treeWidget->addTopLevelItem(item);
        }  catch (std::exception& ex) {
            continue;
        }

    }

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

// When the button next to the Icon box is clicked.
// Shows a file dialog and lets the user pick a .png
void MainWindow::on_locateIcon_clicked() {
    QString selectedIcon = QFileDialog::getOpenFileName(this, "Choose Icon", homedir, "PNG Image (*.png)");

    // Sets the icon box to the icon's file location
    ui->iconBox->setText(selectedIcon);

    if (selectedIcon != "") {
        // Set the app icon
        QImage appIcon(selectedIcon);
        ui->iconImage->setPixmap(getResizedPixmap(appIcon));
    }
    else {
        // Set the question mark icon
        QImage questionMarkIcon(":/Resources/question.png");
        ui->iconImage->setPixmap(getResizedPixmap(questionMarkIcon));
    }


}

// When the button next to the App box is clicked.
// Shows a file dialog and lets the user pick an executable
void MainWindow::on_locateApp_clicked() {
    QString selectedApp = QFileDialog::getOpenFileName(this, "Choose App", homedir);

    // Sets the icon box to the icon's file location
    ui->appBox->setText(selectedApp);
}

// When the dialog OK button is clicked
void MainWindow::on_dialogButtons_accepted() {
    // TODO: Fix the app not removing the .desktop file

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

    ui->nameBox->setText("");
    ui->appBox->setText("");
    ui->iconBox->setText("");
    ui->terminalCheckbox->setChecked(false);

    // Set the question mark icon
    QImage questionMarkIcon(":/Resources/question.png");
    ui->iconImage->setPixmap(getResizedPixmap(questionMarkIcon));

}

// Clear the values when the user clicks the Dialog Cancel button
void MainWindow::on_dialogButtons_rejected() {
    ui->nameBox->setText("");
    ui->appBox->setText("");
    ui->iconBox->setText("");
    ui->terminalCheckbox->setChecked(false);

    // Set the question mark icon
    QImage questionMarkIcon(":/Resources/question.png");
    ui->iconImage->setPixmap(getResizedPixmap(questionMarkIcon));
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column) {
    QString data = item->text(0);
    ui->appDetailsBox->setPlainText(data);
}

