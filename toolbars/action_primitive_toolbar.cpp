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
    connect(rotateAction, SIGNAL(triggered()),SLOT(setRotate()));

    translateAction         = new QAction(QString::fromLocal8Bit("&Переместить"), this);
    this->addAction(translateAction);
    connect(translateAction, SIGNAL(triggered()),SLOT(setTranslate()));

    subtractionAction       = new QAction(QString::fromLocal8Bit("&Вычесть"), this);
    this->addAction(subtractionAction);

    groupAction             = new QAction(QString::fromLocal8Bit("&Сгрупировать"), this);
    this->addAction(groupAction);
    connect(groupAction, SIGNAL(triggered()),SLOT(setGroup()));

    intersectionAction      = new QAction(QString::fromLocal8Bit("&Пересечение"), this);
    this->addAction(intersectionAction);
}

void ActionPrimitiveToolBar::setTranslate()
{
    changeEvent(MEV_TRANSLATE);
}

void ActionPrimitiveToolBar::setRotate()
{
    changeEvent(MEV_ROTATE);
}

void ActionPrimitiveToolBar::setGroup()
{
    changeEvent(MEV_GROUP);
}

void ActionPrimitiveToolBar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}

