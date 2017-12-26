#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include "src/resource.h"

class GLWidget;

class ContextMenu : public QMenu
{
public:
    ContextMenu(int type, QWidget *parent);
    void createPrimitiveContexMenu();
    void createSceneContexMenu();
public:
    GLWidget    *pGLW;
    QAction     *primitiveDeleteAction;
    QAction     *primitivePropertiesAction;

};

#endif // CONTEXTMENU_H
