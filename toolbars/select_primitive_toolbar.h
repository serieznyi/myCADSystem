// Добавлением элементов на сцену

#ifndef PRIMITIVETOOLBAR_H
#define PRIMITIVETOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "resource.h"

class MainWindow;

class SelectPrimitiveToolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit SelectPrimitiveToolbar(QWidget *parent);

private:
    void createActions();
    void changeEvent(int i);

private:
    QPushButton             *pb_point;
    QPushButton             *pb_line;
    QPushButton             *pb_quad;
    QPushButton             *pb_pyramid;
    QPushButton             *pb_sphere;
    QHBoxLayout             *lt_global;

    QAction                 *pointAction;
    QAction                 *lineAction;
    QAction                 *quadAction;
    QAction                 *triangleAction;
    QAction                 *sphereAction;
    MainWindow *pMW;

public slots:
    void addCube();
    void addPyramid();
};

#endif // PRIMITIVETOOLBAR_H
