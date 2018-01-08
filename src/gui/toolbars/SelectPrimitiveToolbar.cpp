#include "SelectPrimitiveToolbar.h"
#include "src/gui/MainWindow.h"

SelectPrimitiveToolbar::SelectPrimitiveToolbar(QWidget *parent) :  QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);

    lt_global       = new QHBoxLayout(this);

    this->setLayout(lt_global);

    createActions();
}

void SelectPrimitiveToolbar::createActions()
{
    quadAction = new QAction(QString::fromLocal8Bit("&Куб"), this);
    this->addAction(quadAction);
    connect(quadAction, SIGNAL(triggered()), SLOT(setCubeAction()));

    triangleAction = new QAction(QString::fromLocal8Bit("&Пирамида"), this);
    this->addAction(triangleAction);
    connect(triangleAction, SIGNAL(triggered()), SLOT(setPyramidAction()));

    sphereAction = new QAction(QString::fromLocal8Bit("&Сфера"), this);
    this->addAction(sphereAction);
    connect(sphereAction, SIGNAL(triggered()), SLOT(setSphereAction()));

}

void SelectPrimitiveToolbar::setCubeAction()
{
    changeEvent(MEL_CUBE);
}

void SelectPrimitiveToolbar::setPyramidAction()
{
    changeEvent(MEL_PYRAMID);
}

void SelectPrimitiveToolbar::setSphereAction()
{
    changeEvent(MEL_SPHERE);
}

void SelectPrimitiveToolbar::changeEvent(int i)
{
    pMW->setPrevEvent(*(pMW->getCurEvent()));
    pMW->setCurEvent(i);
}
