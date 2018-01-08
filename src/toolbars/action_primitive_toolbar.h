// Управления объектами сцены

#ifndef ACTION_PRIMITIVE_TOOLBAR_H
#define ACTION_PRIMITIVE_TOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "src/resource.h"
#include "../mainwindow.h"

class ActionPrimitiveToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ActionPrimitiveToolBar(QWidget *parent = 0);

private:
    void createActions();
    void changeEvent(int i);

private:
    MainWindow *pMW;

    QHBoxLayout             *lt_global;

    QAction                 *rotateAction;
    QAction                 *translateAction;
    QAction                 *scaleAction;
    QAction                 *stretchAction;
    QAction                 *subtractionAction;
    QAction                 *groupAction;
    QAction                 *intersectionAction;

public slots:
    void setTranslateAction();
    void setRotateAction();
    void setScaleAction();
    void setStretchAction();
    void setGroupAction();
    void setSubstractAction();
    void setIntersectAction();


};

#endif // ACTION_PRIMITIVE_TOOLBAR_H
