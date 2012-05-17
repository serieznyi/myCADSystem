#include "action_primitive_toolbar.h"
#include "mainwindow.h"

ActionPrimitiveToolBar::ActionPrimitiveToolBar(QWidget *parent) :  QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);

    lt_global           = new QHBoxLayout(this);
    pb_translate        = new QPushButton();
    pb_rotate           = new QPushButton();
    pb_subtraction      = new QPushButton();
    pb_group            = new QPushButton();
    pb_intersection     = new QPushButton();

    lt_global->addWidget(pb_translate);
    lt_global->addWidget(pb_rotate);
    lt_global->addWidget(pb_subtraction);
    lt_global->addWidget(pb_group);
    lt_global->addWidget(pb_intersection);
    lt_global->addStretch(5);
    this->setLayout(lt_global);

    createActions();
}

void ActionPrimitiveToolBar::createActions()
{
    rotateAction            = new QAction(QString::fromLocal8Bit("&Повернуть"), this);
    this->addAction(rotateAction);
    connect(rotateAction, SIGNAL(triggered()),SLOT(setRotateAction()));

    translateAction         = new QAction(QString::fromLocal8Bit("&Переместить"), this);
    this->addAction(translateAction);
    connect(translateAction, SIGNAL(triggered()),SLOT(setTranslateAction()));

    subtractionAction       = new QAction(QString::fromLocal8Bit("&Вычесть"), this);
    this->addAction(subtractionAction);
    connect(subtractionAction, SIGNAL(triggered()),SLOT(setSubstractAction()));

    groupAction             = new QAction(QString::fromLocal8Bit("&Сгрупировать"), this);
    this->addAction(groupAction);
    connect(groupAction, SIGNAL(triggered()),SLOT(setGroupAction()));

    intersectionAction      = new QAction(QString::fromLocal8Bit("&Пересечение"), this);
    this->addAction(intersectionAction);
    connect(intersectionAction, SIGNAL(triggered()),SLOT(setIntersectAction()));
}

void ActionPrimitiveToolBar::setTranslateAction()
{
    changeEvent(MEV_TRANSLATE);
}

void ActionPrimitiveToolBar::setRotateAction()
{
    changeEvent(MEV_ROTATE);
}

void ActionPrimitiveToolBar::setGroupAction()
{
    changeEvent(MEV_GROUP);
}

void ActionPrimitiveToolBar::setSubstractAction()
{
    changeEvent(MEV_SUBSTRACT);
}

void ActionPrimitiveToolBar::setIntersectAction()
{
    changeEvent(MEV_INTERSECT);
}

void ActionPrimitiveToolBar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}

