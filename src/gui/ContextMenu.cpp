#include "ContextMenu.h"
#include "src/GLWidget.h"

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
    primitiveDeleteAction = new QAction("&Удалить", this);
    connect(primitiveDeleteAction, SIGNAL(triggered()), pGLW, SLOT(deletePrimitive()));
    this->addSeparator();
    this->addAction(primitiveDeleteAction);

    primitivePropertiesAction = new QAction("&Свойства", this);
    this->addAction(primitivePropertiesAction);
}

void ContextMenu::createSceneContexMenu()
{

}
