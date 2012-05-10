#include "menubar.h"
#include "mainwindow.h"

MenuBar::MenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);

    createActions();

    menu_file = new QMenu(QString::fromLocal8Bit("Файл"));
    this->addMenu(menu_file);
        menu_open = new QMenu(QString::fromLocal8Bit("Открыть"));
        menu_file->addMenu(menu_open);
        menu_file->addAction(close_prog);
        connect(close_prog, SIGNAL(triggered()),pMW, SLOT(close()));
    menu_scene_action = new QMenu(QString::fromLocal8Bit("Сцена"));
    this->addMenu(menu_scene_action);
    menu_select_primitive = new QMenu(QString::fromLocal8Bit("Примитивы"));
    this->addMenu(menu_select_primitive);
    menu_primitive_action = new QMenu(QString::fromLocal8Bit("Действия над примитивами"));
    this->addMenu(menu_primitive_action);
    menu_help = new QMenu(QString::fromLocal8Bit("Помощь"));
    this->addMenu(menu_help);
        menu_help->addAction(show_about);
        connect(show_about, SIGNAL(triggered()),pMW, SLOT(showAbout()));

    this->addMenu(menu_help);
}

void MenuBar::createActions()
{
    show_about = new QAction(QString::fromLocal8Bit("О программе"),this);
    close_prog = new QAction(QString::fromLocal8Bit("Выход"),this);
}
