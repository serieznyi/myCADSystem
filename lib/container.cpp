#include "container.h"

Container::Container(Primitive *prim)
{
    primitive           = prim;
    rotateList          = new QList<Rotate*>();
    translateList       = new QList<Translate*>();
    scaleList           = new QList<Scale*>();
}

Container::Container(Primitive *prim, Translate *translate)
{
    primitive           = prim;
    rotateList          = new QList<Rotate*>();
    translateList       = new QList<Translate*>();
    scaleList           = new QList<Scale*>();

    addTranslate(translate);
}

void Container::addTranslate(Translate *trans)
{
    translateList->append(trans);
}

void Container::addRotate(Rotate *rot)
{
    rotateList->append(rot);
}

void Container::addScale(Scale *scale)
{
    scaleList->append(scale);
}

QList<Translate*>* Container::getTranslateList()
{
    return translateList;
}

QList<Rotate*>* Container::getRotateList()
{
    return rotateList;
}

QList<Scale *> *Container::getScaleList()
{
    return scaleList;
}

Translate* Container::getTranslate()
{
    return translateList->last();
}

Scale* Container::getScale()
{
    return scaleList->last();
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

    for(int i=0;i<scaleList->size();i++)
        scaleList->at(i)->Apply(mode);

    primitive->Apply(mode);
}


