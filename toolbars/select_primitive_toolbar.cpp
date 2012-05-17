#include "select_primitive_toolbar.h"
#include "mainwindow.h"

SelectPrimitiveToolbar::SelectPrimitiveToolbar(QWidget *parent) :  QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);

    lt_global       = new QHBoxLayout(this);
    pb_point        = new QPushButton();
    pb_line         = new QPushButton();
    pb_quad         = new QPushButton();
    pb_pyramid      = new QPushButton();
    pb_sphere       = new QPushButton();
    /////////////////////////////////////////
    //pb_quad->setStyleSheet("color: blue;");


    lt_global->addWidget(pb_point);
    lt_global->addWidget(pb_line);
    lt_global->addWidget(pb_quad);
    lt_global->addWidget(pb_pyramid);
    lt_global->addWidget(pb_sphere);
    lt_global->addStretch(5);

    this->setLayout(lt_global);

    createActions();
}

void SelectPrimitiveToolbar::createActions()
{
    pointAction = new QAction(QString::fromLocal8Bit("&Точка"), this);
    this->addAction(pointAction);

    lineAction = new QAction(QString::fromLocal8Bit("&Линия"), this);
    this->addAction(lineAction);

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
