#include "SceneControlToolbar.h"
#include "src/gui/MainWindow.h"

SceneControlToolbar::SceneControlToolbar(QWidget *parent):QToolBar(parent)
{
        pMW = dynamic_cast<MainWindow*>(parent);

       lt_global            = new QHBoxLayout(this);

       this->setLayout(lt_global);

       createActions();
}

void SceneControlToolbar::createActions()
{
    cameraPosAction = new QAction(QString::fromLocal8Bit("&Переместить камеру"), this);
    connect(cameraPosAction, SIGNAL(triggered()),SLOT(setCameraTranslateAction()));

    cameraRotAction = new QAction(QString::fromLocal8Bit("&Повернуть камеру"), this);
    connect(cameraRotAction, SIGNAL(triggered()), SLOT(setCameraRotAction()));

    cameraZoomAction = new QAction(QString::fromLocal8Bit("&Масштаб"), this);
    connect(cameraZoomAction, SIGNAL(triggered()), SLOT(setCameraZoomAction()));

    this->addAction(cameraPosAction);
    this->addAction(cameraRotAction);
    this->addAction(cameraZoomAction);
}

void SceneControlToolbar::setCameraTranslateAction()
{
    changeEvent(MEV_CAMERA_TRANSLATE);
}

void SceneControlToolbar::setCameraRotAction()
{
    changeEvent(MEV_CAMERA_ROTATE);
}

void SceneControlToolbar::setCameraZoomAction()
{
    changeEvent(MEV_CAMERA_ZOOM);
}

void SceneControlToolbar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}
