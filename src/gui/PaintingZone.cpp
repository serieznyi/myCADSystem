#include "PaintingZone.h"

PaintingZone::PaintingZone(QWidget *parent) : QWidget(parent)
{
    widTop              = new GLWidget(parent);
    widPerspective      = new GLWidget(parent);
    widFront            = new GLWidget(parent);
    widRight            = new GLWidget(parent);
    sp_global           = new QSplitter(Qt::Vertical);
    sp_top              = new QSplitter(Qt::Horizontal);
    sp_down             = new QSplitter(Qt::Horizontal);
    lay_global          = new QVBoxLayout();
    widTop->setProjection(MPJ_TOP);
    widPerspective->setProjection(MPJ_PERSPECTIVE);
    widFront->setProjection(MPJ_FRONT);
    widRight->setProjection(MPJ_RIGHT);
    saveProjectionLastState();
    sp_top->addWidget(widTop);
    sp_top->addWidget(widPerspective);
    sp_down->addWidget(widFront);
    sp_down->addWidget(widRight);
    sp_global->addWidget(sp_top);
    sp_global->addWidget(sp_down);
    lay_global->addWidget(sp_global);
    this->setLayout(lay_global);
}

void PaintingZone::Update()
{
    widPerspective->repaint();
    widTop->repaint();
    widFront->repaint();
    widRight->repaint();
}

void PaintingZone::setMaximum(int i)
{
    switch(i)
    {
    case MPJ_FRONT:
        setAllUnvisible(true);
        widFront->setVisible(true);
        break;
    case MPJ_TOP:
        setAllUnvisible(true);
        widTop->setVisible(true);
        break;
    case MPJ_RIGHT:
        setAllUnvisible(true);
        widRight->setVisible(true);
        break;
    case MPJ_PERSPECTIVE:
        setAllUnvisible(true);
        widPerspective->setVisible(true);
        break;
    }
}

void PaintingZone::setAllUnvisible(bool a)
{
    widTop->setHidden(a);
    widFront->setHidden(a);
    widRight->setHidden(a);
    widPerspective->setHidden(a);
}

void PaintingZone::saveProjectionLastState()
{
    widPerspective->SaveLastState();
    widTop->SaveLastState();
    widFront->SaveLastState();
    widRight->SaveLastState();
}

void PaintingZone::loadProjectionLastState()
{
    widPerspective->LoadLastState();
    widTop->LoadLastState();
    widFront->LoadLastState();
    widRight->LoadLastState();
}