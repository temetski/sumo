#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication> // For QSettings organization/application name

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set organization and application name for QSettings
    QCoreApplication::setOrganizationName("SUMO");
    QCoreApplication::setApplicationName("SUMO-GUI-Qt");

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
