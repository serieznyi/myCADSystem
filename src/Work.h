// Работа (Проект)
#ifndef WORK_H
#define WORK_H

#include <QOpenGLWidget>
#include <GL/glu.h>
#include <cstdlib>
#include <ctime>
#include <src/Domain/Primitive.h>
#include <src/Domain/Container.h>
#include "src/constants.h"

class MainWindow;

class Work
{
public:
    explicit Work(QWidget *parent);
    void drawWork(bool mode=true);
    void addPrimitive(int i, QPoint pos=QPoint(0,0));                           // Добавление объекта на сцену
    void addAction(int i);                              // Применение действия
    long generateGID();                                 // Генерация идентификатора для события
    MCOLOR *generateIDColor();
    MCOLOR *generateColor();
    QList<Container *> *getList();
    void deletePrimitive(long index);
    void setGroupObj1(long i);
    void setGroupObj2(long i);
    long getGroupObj1();
    long getGroupObj2();
public:
    int                      real_color[3];
private:
    long                      forGroupID[2];
    MainWindow  *pMW;
    QList<Container*>          *element_list;             //  Список элементов сцены
    long                        current_free_id;           //  Текущий свободный идентификатор
    int                         current_free_color[3];     //
    GLUquadric                  *quadric;
};


#endif // WORK_H
