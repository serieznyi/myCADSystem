#include "contextmenu.h"
#include "glwidget.h"

ContextMenu::ContextMenu(int type, QWidget *parent):QMenu(parent)
{
    pGLW = dynamic_cast<GLWidget*>(parent);
    switch(type)
    {
    case MCM_SCENE: createSceneContexMenu(); break;
    case MCM_PRIMITIVE: createPrimitiveContexMenu(); break;
    }
}

void ContextMenu::createPrimitiveContexMenu()
{
    primitiveDeleteAction = new QAction(QString::fromLocal8Bit("&Удалить"), this);
    connect(primitiveDeleteAction, SIGNAL(triggered()), pGLW, SLOT(deletePrimitive()));
    this->addSeparator();
    this->addAction(primitiveDeleteAction);

    primitivePropertiesAction = new QAction(QString::fromLocal8Bit("&Свойства"), this);
    this->addAction(primitivePropertiesAction);
}

void ContextMenu::createSceneContexMenu()
{

}
