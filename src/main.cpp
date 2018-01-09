#include <QApplication>
#include <QtWidgets/QDesktopWidget>
#include "src/gui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QRect desktopGeometry = application.desktop()->screenGeometry();

    MainWindow *mainWindow = new MainWindow(desktopGeometry.width(), desktopGeometry.height());

    mainWindow->show();

    return application.exec();
}
