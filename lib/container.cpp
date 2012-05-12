#include "container.h"

Container::Container(Primitive *prim)
{
    primitive           = prim;
    rotateList          = new QList<Rotate*>();
    translateList       = new QList<Translate*>();
}

void Container::addTranslate(Translate *trans)
{
    translateList->append(trans);
}

void Container::addRotate(Rotate *rot)
{
    rotateList->append(rot);
}

QList<Translate*>* Container::getTranslateList()
{
    return translateList;
}

QList<Rotate*>* Container::getRotateList()
{
    return rotateList;
}

Translate* Container::getTranslate()
{
    return translateList->last();
}

Rotate* Container::getRotate()
{
    return rotateList->last();
}

Primitive* Container::getPrimitive()
{
    return primitive;
}

void Container::draw(int mode)
{
    for(int i=0;i<translateList->size();i++)
        translateList->at(i)->Apply(mode);

    for(int i=0;i<rotateList->size();i++)
        rotateList->at(i)->Apply(mode);

    primitive->Apply(mode);
}


