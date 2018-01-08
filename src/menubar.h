// Меню-бар
#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>

class MainWindow;

class MenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = 0);
    void createActions();
public:
    MainWindow             *pMW;
    QMenu           *menu_file;
    QAction               *action_open;
    QAction               *action_save;
    QAction               *action_save_to;
    QAction               *action_exit;
    QMenu           *menu_scene_action;
    QAction               *actionTranslateCamera;
    QAction               *actionRotateCamera;
    QAction               *actionZoomCamera;
    QMenu           *menu_select_primitive;
    QAction               *actionCube;
    QAction               *actionPyramid;
    QAction               *actionSphere;
    QMenu           *menu_primitive_action;
    QAction               *actionTranslate;
    QAction               *actionRotate;
    QAction               *actionGroup;
    QMenu           *menu_help;
    QAction               *action_about;

};

#endif // MENUBAR_H
