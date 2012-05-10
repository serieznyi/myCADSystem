// ћеню-бар
#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>

class MainWindow;

class MenuBar : public QMenuBar
{

public:
    explicit MenuBar(QWidget *parent = 0);
    void createActions();
public:
    MainWindow             *pMW;
    QMenu           *menu_file;
    QMenu               *menu_open;
    QMenu               *menu_save;
    QMenu               *menu_save_to;
    QMenu           *menu_scene_action;
    QMenu           *menu_select_primitive;
    QMenu           *menu_primitive_action;
    QMenu           *menu_help;
    QMenu               *menu_about;

    QAction         *close_prog;
    QAction         *show_about;

};

#endif // MENUBAR_H
