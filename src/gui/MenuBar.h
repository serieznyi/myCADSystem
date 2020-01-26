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
    QMenu           *fileMenu;
    QAction               *fileOpenAction;
    QAction               *fileSaveAction;
    QAction               *fileSaveToAction;
    QAction               *exitAction;
    QMenu           *sceneActionMenu;
    QAction               *actionTranslateCamera;
    QAction               *actionRotateCamera;
    QAction               *actionZoomCamera;
    QMenu           *primitiveMenu;
    QAction               *actionCube;
    QAction               *actionPyramid;
    QAction               *actionSphere;
    QMenu           *primitiveActionMenu;
    QAction               *actionTranslate;
    QAction               *actionRotate;
    QAction               *actionGroup;
    QMenu           *helpMenu;
    QAction               *action_about;

 private:
  void primitiveChangeEvent(int i);

 public slots:
  void setSphereAction();
  void setPyramidAction();
  void setCubeAction();
};

#endif // MENUBAR_H
