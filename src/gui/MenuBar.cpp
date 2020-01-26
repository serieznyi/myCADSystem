#include "MenuBar.h"
#include "src/gui/MainWindow.h"

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
  connect(actionTranslateCamera, SIGNAL(triggered()), pMW->getSceneControlToolbar(), SLOT(setCameraTranslateAction()));

  actionRotateCamera = new QAction("Повернуть камеру", this);
  sceneActionMenu->addAction(actionRotateCamera);
  connect(actionRotateCamera, SIGNAL(triggered()), pMW->getSceneControlToolbar(), SLOT(setCameraRotAction()));

  actionZoomCamera = new QAction("Изменить масштаб", this);
  sceneActionMenu->addAction(actionZoomCamera);
  connect(actionZoomCamera, SIGNAL(triggered()), pMW->getSceneControlToolbar(), SLOT(setCameraZoomAction()));

  // Primitives
  actionCube = new QAction("Куб", this);
  primitiveMenu->addAction(actionCube);
  connect(actionCube, SIGNAL(triggered()), SLOT(setCubeAction()));

  actionSphere = new QAction("Сфера", this);
  primitiveMenu->addAction(actionSphere);
  connect(actionSphere, SIGNAL(triggered()), SLOT(setSphereAction()));

  actionPyramid = new QAction("Пирамида", this);
  primitiveMenu->addAction(actionPyramid);
  connect(actionPyramid, SIGNAL(triggered()), SLOT(setPyramidAction()));

  // Actions
  actionTranslate = new QAction("Переместить", this);
  primitiveActionMenu->addAction(actionTranslate);
  connect(actionTranslate, SIGNAL(triggered()), pMW->getActionPrimitiveToolbar(), SLOT(setTranslateAction()));

  actionRotate = new QAction("Повернуть", this);
  primitiveActionMenu->addAction(actionRotate);
  connect(actionRotate, SIGNAL(triggered()), pMW->getActionPrimitiveToolbar(), SLOT(setRotateAction()));

  actionGroup = new QAction("Сгрупировать", this);
  primitiveActionMenu->addAction(actionGroup);
  connect(actionGroup, SIGNAL(triggered()), pMW->getActionPrimitiveToolbar(), SLOT(setGroupAction()));

}

void MenuBar::setCubeAction() {

  primitiveChangeEvent(MEL_CUBE);
}

void MenuBar::setPyramidAction() {
  primitiveChangeEvent(MEL_PYRAMID);
}

void MenuBar::setSphereAction() {
  primitiveChangeEvent(MEL_SPHERE);
}

void MenuBar::primitiveChangeEvent(int i) {
  pMW->setPrevEvent(*(pMW->getCurEvent()));
  pMW->setCurEvent(i);
}
