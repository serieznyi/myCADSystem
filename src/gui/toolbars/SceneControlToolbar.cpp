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
    cameraPosAction = new QAction("&Переместить камеру", this);
    connect(cameraPosAction, SIGNAL(triggered()),SLOT(setCameraTranslateAction()));

    cameraRotAction = new QAction("&Повернуть камеру", this);
    connect(cameraRotAction, SIGNAL(triggered()), SLOT(setCameraRotAction()));

    cameraZoomAction = new QAction("&Масштаб", this);
    connect(cameraZoomAction, SIGNAL(triggered()), SLOT(setCameraZoomAction()));

    this->addAction(cameraPosAction);
    this->addAction(cameraRotAction);
    this->addAction(cameraZoomAction);
}

void SceneControlToolbar::setCameraTranslateAction()
{
    changeEvent(CAMERA_TRANSLATE);
}

void SceneControlToolbar::setCameraRotAction()
{
    changeEvent(CAMERA_ROTATE);
}

void SceneControlToolbar::setCameraZoomAction()
{
    changeEvent(CAMERA_ZOOM);
}

void SceneControlToolbar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}
