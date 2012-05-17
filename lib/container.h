//  Контейнер хранящий прмитив и все связные с ним операции

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QList>
#include "lib/primitive/primitive.h"
#include "lib/action/translate.h"
#include "lib/action/rotate.h"

class Container
{
public:
    Container(Primitive *prim);
    Container(Primitive *prim, Translate *translate);
    void addTranslate(Translate *trans);
    void addRotate(Rotate *rot);
    QList<Translate*>* getTranslateList();
    QList<Rotate*>* getRotateList();
    Translate* getTranslate();
    Rotate* getRotate();
    Primitive* getPrimitive();
    void draw(int mode);
private:
    Primitive *primitive;
    QList<Translate*>* translateList;
    QList<Rotate*>* rotateList;
};

#endif // CONTAINER_H
