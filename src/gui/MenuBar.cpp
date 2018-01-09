#include "MenuBar.h"
#include "src/gui/MainWindow.h"

MenuBar::MenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);

    menu_file = new QMenu("Файл");
        this->addMenu(menu_file);
    menu_scene_action = new QMenu("Сцена");
        this->addMenu(menu_scene_action);
    menu_select_primitive = new QMenu("Примитивы");
        this->addMenu(menu_select_primitive);
    menu_primitive_action = new QMenu("Действия над примитивами");
        this->addMenu(menu_primitive_action);
    menu_help = new QMenu("Помощь");
        this->addMenu(menu_help);

    createActions();
}

void MenuBar::createActions()
{
    action_open         = new QAction("Открыть",this);
    action_save         = new QAction("Сохранить",this);
    action_save_to      = new QAction("Сохранить как...",this);
    action_exit         = new QAction("Выход",this);

    actionTranslateCamera   = new QAction("Переместить камеру",this);
    actionRotateCamera      = new QAction("Повернуть камеру",this);
    actionZoomCamera        = new QAction("Изменить масштаб",this);

    actionCube          = new QAction("Куб",this);
    actionSphere        = new QAction("Сфера",this);
    actionPyramid       = new QAction("Пирамида",this);

    actionTranslate         = new QAction("Переместить",this);
    actionRotate            = new QAction("Повернуть",this);
    actionGroup             = new QAction("Сгрупировать",this);

    action_about        = new QAction("О программе",this);

    menu_file->addAction(action_open);
    menu_file->addSeparator();
    menu_file->addAction(action_save);
    menu_file->addAction(action_save_to);
        connect(action_save_to, SIGNAL(triggered()),pMW, SLOT(saveTo()));
    menu_file->addSeparator();
    menu_file->addAction(action_exit);
        connect(action_exit, SIGNAL(triggered()),pMW, SLOT(close()));
    menu_help->addAction(action_about);


    menu_scene_action->addAction(actionTranslateCamera);
        connect(actionTranslateCamera, SIGNAL(triggered()),pMW->getSceneControlToolbar(), SLOT(setCameraTranslateAction()));
    menu_scene_action->addAction(actionRotateCamera);
        connect(actionRotateCamera, SIGNAL(triggered()),pMW->getSceneControlToolbar(), SLOT(setCameraRotAction()));
    menu_scene_action->addAction(actionZoomCamera);
        connect(actionZoomCamera, SIGNAL(triggered()),pMW->getSceneControlToolbar(), SLOT(setCameraZoomAction()));


    menu_select_primitive->addAction(actionCube);
        connect(actionTranslateCamera, SIGNAL(triggered()),pMW->getSelectPrimitiveToolbar(), SLOT(setCubeAction()));
    menu_select_primitive->addAction(actionPyramid);
        connect(actionRotateCamera, SIGNAL(triggered()),pMW->getSelectPrimitiveToolbar(), SLOT(setPyramidAction()));
    menu_select_primitive->addAction(actionSphere);
        connect(actionZoomCamera, SIGNAL(triggered()),pMW->getSelectPrimitiveToolbar(), SLOT(setSphereAction()));


    menu_primitive_action->addAction(actionTranslate);
        connect(actionTranslate, SIGNAL(triggered()),pMW->getActionPrimitiveToolbar(), SLOT(setTranslateAction()));
    menu_primitive_action->addAction(actionRotate);
        connect(actionRotate, SIGNAL(triggered()),pMW->getActionPrimitiveToolbar(), SLOT(setRotateAction()));
    menu_primitive_action->addAction(actionGroup);
        connect(actionGroup, SIGNAL(triggered()),pMW->getActionPrimitiveToolbar(), SLOT(setGroupAction()));

}
