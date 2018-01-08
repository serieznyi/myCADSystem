// Добавлением элементов на сцену

#ifndef PRIMITIVETOOLBAR_H
#define PRIMITIVETOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "src/resource.h"

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
    QHBoxLayout             *lt_global;

    QAction                 *quadAction;
    QAction                 *triangleAction;
    QAction                 *sphereAction;
    MainWindow              *pMW;

public slots:
    void setCubeAction();
    void setPyramidAction();
    void setSphereAction();
};

#endif // PRIMITIVETOOLBAR_H
