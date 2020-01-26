// Меню-бар
#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>

class MainWindow;

class MenuBar : public QMenuBar {
 Q_OBJECT

 public:
  explicit MenuBar(QWidget *parent = 0);
  void createActions();
 public:
  MainWindow *pMW;
  QMenu *fileMenu;
  QAction *fileOpenAction;
  QAction *fileSaveAction;
  QAction *fileSaveToAction;
  QAction *exitAction;
  QMenu *sceneActionMenu;
  QAction *actionTranslateCamera;
  QAction *actionRotateCamera;
  QAction *actionZoomCamera;
  QMenu *primitiveMenu;
  QAction *actionCube;
  QAction *actionPyramid;
  QAction *actionSphere;
  QMenu *primitiveActionMenu;
  QAction *actionTranslate;
  QAction *actionRotate;
  QAction *actionGroup;
  QMenu *helpMenu;
  QAction *action_about;

 private:
  void choosePrimitiveEvent(int i);
  void choosePrimitiveActionEvent(int i);

 public slots:
  void choosePrimitiveSphereAction();
  void choosePrimitivePyramidAction();
  void choosePrimitiveCubeAction();
  void choosePrimitiveTranslateAction();
  void choosePrimitiveRotateAction();
  void choosePrimitiveGroupAction();
  void chooseCameraTranslateAction();
  void chooseCameraRotAction();
  void chooseCameraZoomAction();
};

#endif // MENUBAR_H
