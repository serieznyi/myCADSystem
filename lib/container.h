//  Контейнер хранящий прмитив и все связные с ним операции

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QList>
#include "lib/lib.h"

class Container
{
public:
    Container(Primitive *prim);
    void addTranslate(Translate *trans);
    void addRotate(Rotate *rot);
private:
    Primitive *primitive;
    QList<Translate*> *translateList;
    QList<Rotate*> *rotateList;
};

#endif // CONTAINER_H
