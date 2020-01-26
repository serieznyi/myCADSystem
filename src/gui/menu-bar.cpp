#include "menu-bar.h"
#include "src/gui/main-window.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
  pMW = dynamic_cast<MainWindow *>(parent);

  fileMenu = new QMenu("Файл");
  this->addMenu(fileMenu);

  sceneActionMenu = new QMenu("Сцена");
  this->addMenu(sceneActionMenu);

  primitiveMenu = new QMenu("Примитивы");
  this->addMenu(primitiveMenu);

  primitiveActionMenu = new QMenu("Действия над примитивами");
  this->addMenu(primitiveActionMenu);

  helpMenu = new QMenu("Помощь");
  this->addMenu(helpMenu);

  createActions();
}

void MenuBar::createActions() {

  // File
  fileOpenAction = new QAction("Открыть", this);
  fileMenu->addAction(fileOpenAction);

  fileMenu->addSeparator();

  fileSaveAction = new QAction("Сохранить", this);
  fileMenu->addAction(fileSaveAction);

  fileSaveToAction = new QAction("Сохранить как...", this);
  fileMenu->addAction(fileSaveToAction);
  connect(fileSaveToAction, SIGNAL(triggered()), pMW, SLOT(saveTo()));

  fileMenu->addSeparator();

  exitAction = new QAction("Выход", this);
  fileMenu->addAction(exitAction);
  connect(exitAction, SIGNAL(triggered()), pMW, SLOT(close()));

  // About
  action_about = new QAction("О программе", this);
  helpMenu->addAction(action_about);

  // Camera actions
  actionTranslateCamera = new QAction("Переместить камеру", this);
  sceneActionMenu->addAction(actionTranslateCamera);
  connect(actionTranslateCamera, SIGNAL(triggered()), SLOT(chooseCameraTranslateAction()));

  actionRotateCamera = new QAction("Повернуть камеру", this);
  sceneActionMenu->addAction(actionRotateCamera);
  connect(actionRotateCamera, SIGNAL(triggered()), SLOT(chooseCameraRotAction()));

  actionZoomCamera = new QAction("Изменить масштаб", this);
  sceneActionMenu->addAction(actionZoomCamera);
  connect(actionZoomCamera, SIGNAL(triggered()), SLOT(chooseCameraZoomAction()));

  // Primitives
  actionCube = new QAction("Куб", this);
  primitiveMenu->addAction(actionCube);
  connect(actionCube, SIGNAL(triggered()), SLOT(choosePrimitiveCubeAction()));

  actionSphere = new QAction("Сфера", this);
  primitiveMenu->addAction(actionSphere);
  connect(actionSphere, SIGNAL(triggered()), SLOT(choosePrimitiveSphereAction()));

  actionPyramid = new QAction("Пирамида", this);
  primitiveMenu->addAction(actionPyramid);
  connect(actionPyramid, SIGNAL(triggered()), SLOT(choosePrimitivePyramidAction()));

  // Primitive actions
  actionTranslate = new QAction("Переместить", this);
  primitiveActionMenu->addAction(actionTranslate);
  connect(actionTranslate, SIGNAL(triggered()), SLOT(choosePrimitiveTranslateAction()));

  actionRotate = new QAction("Повернуть", this);
  primitiveActionMenu->addAction(actionRotate);
  connect(actionRotate, SIGNAL(triggered()), SLOT(choosePrimitiveRotateAction()));

  actionGroup = new QAction("Сгрупировать", this);
  primitiveActionMenu->addAction(actionGroup);
  connect(actionGroup, SIGNAL(triggered()), SLOT(choosePrimitiveGroupAction()));

}

void MenuBar::choosePrimitiveCubeAction() {

  choosePrimitiveEvent(MEL_CUBE);
}

void MenuBar::choosePrimitivePyramidAction() {
  choosePrimitiveEvent(MEL_PYRAMID);
}

void MenuBar::choosePrimitiveSphereAction() {
  choosePrimitiveEvent(MEL_SPHERE);
}

void MenuBar::choosePrimitiveEvent(int i) {
  pMW->setPrevEvent(*(pMW->getCurEvent()));
  pMW->setCurEvent(i);
}

void MenuBar::choosePrimitiveTranslateAction() {
  choosePrimitiveActionEvent(ACTION_TRANSLATE);
}

void MenuBar::choosePrimitiveRotateAction() {
  choosePrimitiveActionEvent(ACTION_ROTATE);
}

void MenuBar::choosePrimitiveGroupAction() {
  choosePrimitiveActionEvent(ACTION_GROUP);
}

void MenuBar::choosePrimitiveActionEvent(int i) {
  pMW->setCurEvent(i);
}

void MenuBar::chooseCameraTranslateAction() {
  pMW->setCurEvent(CAMERA_TRANSLATE);
}

void MenuBar::chooseCameraRotAction() {
  pMW->setCurEvent(CAMERA_ROTATE);
}

void MenuBar::chooseCameraZoomAction() {
  pMW->setCurEvent(CAMERA_ZOOM);
}