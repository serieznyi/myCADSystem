// Управления объектами сцены

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "resource.h"

class MainWindow;

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

    QPushButton             *pb_translate;
    QPushButton             *pb_rotate;
    QPushButton             *pb_subtraction;
    QPushButton             *pb_group;
    QPushButton             *pb_intersection;

    QHBoxLayout             *lt_global;

    QAction                 *rotateAction;
    QAction                 *translateAction;
    QAction                 *subtractionAction;
    QAction                 *groupAction;
    QAction                 *intersectionAction;

public slots:
    void setTranslateAction();
    void setRotateAction();
    void setGroupAction();
    void setSubstractAction();
    void setIntersectAction();


};

#endif // TOOLBAR_H
