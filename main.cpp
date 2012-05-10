// Точка входа в программу

#include <QtGui/QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow(a.desktop()->screenGeometry().width(),
                                  a.desktop()->screenGeometry().height());
    w->show();
    return a.exec();
}
