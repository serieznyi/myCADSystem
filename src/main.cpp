// РўРѕС‡РєР° РІС…РѕРґР° РІ РїСЂРѕРіСЂР°РјРјСѓ

#include <QApplication>
#include <QtWidgets/QDesktopWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow(a.desktop()->screenGeometry().width(),
                                   a.desktop()->screenGeometry().height());
    w->show();
    return a.exec();
}
