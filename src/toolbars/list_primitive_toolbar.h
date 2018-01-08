//  Список примитивов сцены

#ifndef LIST_PRIMITIVE_TOOLBAR_H
#define LIST_PRIMITIVE_TOOLBAR_H

#include <QToolBar>
#include <QListWidget>
#include <QHBoxLayout>
#include "src/work.h"
#include "src/lib/primitive/primitive.h"

class MainWindow;

class ListPrimitiveToolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit ListPrimitiveToolbar(QWidget *parent);
    void delPrimitive(Primitive *a);
    void UpdateList();
    void addPrimitive(Primitive *prim);
    QString getName(Primitive *element);
/*
    template <typename T>
    void addPrimitive(T *a)
    {
        lstWidget_primList->addItem(new QListWidgetItem(getName(a)));
        this->repaint();
    }

    template <typename T>
    QString getName(T *element)
    {
        switch(element->getTypeName())
        {
            case MEL_CUBE: return "Куб"; break;
            case MEL_PYRAMID: return "Пирамида"; break;
        }
    }*/
    
public:
    QListWidget             *lstWidget_primList;
    QHBoxLayout             *lt_global;
    MainWindow              *pMW;
    Work                    *currentWork;

signals:

public slots:
    
};

#endif // LIST_PRIMITIVE_TOOLBAR_H
