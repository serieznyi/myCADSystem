// ћеню-бар
#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>

class MenuBar : public QMenuBar
{

public:
    explicit MenuBar(QWidget *parent = 0);

    QMenu           *menu_file;
    QMenu               *menu_open;
    QMenu               *menu_exit;
    QMenu           *menu_scene_action;
    QMenu           *menu_select_primitive;
    QMenu           *menu_primitive_action;
    QMenu           *menu_help;
    QMenu               *menu_about;
    QAction         *close_prog;

};

#endif // MENUBAR_H
