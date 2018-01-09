#include "ActionPrimitiveToolBar.h"
#include "src/gui/MainWindow.h"

ActionPrimitiveToolBar::ActionPrimitiveToolBar(QWidget *parent) :  QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);

    lt_global           = new QHBoxLayout(this);

    this->setLayout(lt_global);

    createActions();
}

void ActionPrimitiveToolBar::createActions()
{
    rotateAction            = new QAction("&Повернуть", this);
    this->addAction(rotateAction);
    connect(rotateAction, SIGNAL(triggered()),SLOT(setRotateAction()));

    translateAction         = new QAction("&Переместить", this);
    this->addAction(translateAction);
    connect(translateAction, SIGNAL(triggered()),SLOT(setTranslateAction()));

    scaleAction         = new QAction("&Масштабировать", this);
    this->addAction(scaleAction);
    connect(scaleAction, SIGNAL(triggered()),SLOT(setScaleAction()));

    stretchAction         = new QAction("&Растянуть", this);
    this->addAction(stretchAction);
    connect(stretchAction, SIGNAL(triggered()),SLOT(setStretchAction()));

    subtractionAction       = new QAction("&Вычесть", this);
    this->addAction(subtractionAction);
    connect(subtractionAction, SIGNAL(triggered()),SLOT(setSubstractAction()));

    groupAction             = new QAction("&Сгрупировать", this);
    this->addAction(groupAction);
    connect(groupAction, SIGNAL(triggered()),SLOT(setGroupAction()));

    intersectionAction      = new QAction("&Пересечение", this);
    this->addAction(intersectionAction);
    connect(intersectionAction, SIGNAL(triggered()),SLOT(setIntersectAction()));
}

void ActionPrimitiveToolBar::setTranslateAction()
{
    changeEvent(ACTION_TRANSLATE);
}

void ActionPrimitiveToolBar::setRotateAction()
{
    changeEvent(ACTION_ROTATE);
}

void ActionPrimitiveToolBar::setStretchAction()
{
    changeEvent(ACTION_STRETCH);
}

void ActionPrimitiveToolBar::setScaleAction()
{
    changeEvent(ACTION_SCALE);
}

void ActionPrimitiveToolBar::setGroupAction()
{
    changeEvent(ACTION_GROUP);
}

void ActionPrimitiveToolBar::setSubstractAction()
{
    changeEvent(ACTION_SUBSTRACT);
}

void ActionPrimitiveToolBar::setIntersectAction()
{
    changeEvent(ACTION_INTERSECT);
}

void ActionPrimitiveToolBar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}

