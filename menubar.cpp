#include "menubar.h"

MenuBar::MenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    menu_file = new QMenu(QString::fromLocal8Bit("Файл"));
    this->addMenu(menu_file);
        menu_open = new QMenu(QString::fromLocal8Bit("Открыть"));
        menu_file->addMenu(menu_open);
        menu_exit = new QMenu(QString::fromLocal8Bit("Выход"));
        menu_file->addMenu(menu_exit);
    menu_scene_action = new QMenu(QString::fromLocal8Bit("Сцена"));
    this->addMenu(menu_scene_action);
    menu_select_primitive = new QMenu(QString::fromLocal8Bit("Примитивы"));
    this->addMenu(menu_select_primitive);
    menu_primitive_action = new QMenu(QString::fromLocal8Bit("Действия над примитивами"));
    this->addMenu(menu_primitive_action);
    menu_help = new QMenu(QString::fromLocal8Bit("Помощь"));
    this->addMenu(menu_help);
        menu_about = new QMenu(QString::fromLocal8Bit("О программе"));
        menu_help->addMenu(menu_about);

    this->addMenu(menu_help);
}
