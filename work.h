// Работа (Проект)
#ifndef WORK_H
#define WORK_H

#include <QGLWidget>
#include <GL/glu.h>
#include "lib/primitive/cube.h"
#include "lib/primitive/pyramid.h"
#include "lib/action/translate.h"
#include "lib/action/rotate.h"
#include "lib/element.h"
#include "resource.h"

class Work
{
public:
    explicit Work();
    void drawWork();
    void addPrimitive(int i);               // Добавление объекта на сцену
    void addAction(int i, double obj[3]);   // Применение действия
    long genGID();                          // Генерация идентификатора для события
    int* genIDColor();
    QList<Element*>* getList();
    QList<int>* getOnlyPrimitiveList();

private:
    QList<Element*>          *element_list;             //  Список элементов сцены
    long                     current_free_id;           //  Текущий свободный идентификатор
    int                      current_free_color[3];     //
    QList<int>               *only_prymitive;           //  Индексы только примитивов
};


#endif // WORK_H
