#include "scene_control_toolbar.h"
#include "mainwindow.h"

SceneControlPanel::SceneControlPanel(QWidget *parent):QToolBar(parent)
{
        pMW = dynamic_cast<MainWindow*>(parent);

       lt_global            = new QHBoxLayout(this);
       pb_camera_pos        = new QPushButton(QString::fromLocal8Bit("Переместить камеру"));
       pb_camera_rot        = new QPushButton(QString::fromLocal8Bit("Повернуть камеру"));
       pb_camera_zoom       = new QPushButton(QString::fromLocal8Bit("Масштаб"));

       lt_global->addWidget(pb_camera_pos);
       lt_global->addWidget(pb_camera_rot);
       lt_global->addWidget(pb_camera_zoom);
       lt_global->addStretch(5);

       this->setLayout(lt_global);

       createActions();
}

void SceneControlPanel::createActions()
{
    cameraPosAction = new QAction(QString::fromLocal8Bit("&Переместить камеру"), this);
    connect(cameraPosAction, SIGNAL(triggered()),SLOT(setCameraPosAction()));

    cameraRotAction = new QAction(QString::fromLocal8Bit("&Повернуть камеру"), this);
    connect(cameraRotAction, SIGNAL(triggered()), SLOT(setCameraRotAction()));

    cameraZoomAction = new QAction(QString::fromLocal8Bit("&Масштаб"), this);
    connect(cameraZoomAction, SIGNAL(triggered()), SLOT(setCameraZoomAction()));

    this->addAction(cameraPosAction);
    this->addAction(cameraRotAction);
    this->addAction(cameraZoomAction);
}

void SceneControlPanel::setCameraPosAction()
{
    changeEvent(MEV_CAMERA_TRANSLATE);
}

void SceneControlPanel::setCameraRotAction()
{
    changeEvent(MEV_CAMERA_ROTATE);
}

void SceneControlPanel::setCameraZoomAction()
{
    changeEvent(MEV_CAMERA_ZOOM);
}

void SceneControlPanel::changeEvent(int i)
{
    pMW->setCurEvent(i);
}
