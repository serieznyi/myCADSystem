#include "work.h"

Work::Work()
{
    element_list                = new QList<Element*>;
    only_prymitive              = new QList<int>;
    current_free_id             = 0;
    current_free_color[0]       = 0;
    current_free_color[1]       = 0;
    current_free_color[2]       = 0;
}

void Work::drawWork()
{
    long size = element_list->size();

    if(size > 0)
        for(int i=0;i<size;i++)
        {
            element_list->at(i)->Apply();
        }
}

void Work::addPrimitive(int i)
{
    switch(i)
    {
    case MEV_PRIM_SPHERE:
    {
        break;
    }
    case MEV_PRIM_QUAD:
    {
        Translate *translate = new Translate(0, 0, 0);
        translate->setGID(genGID());
        element_list->append(translate);
            Rotate *rotate = new Rotate(0,0,0);
            rotate->setGID(genGID());
            element_list->append(rotate);
                Cube *cube = new Cube(1.0f);
                cube->setGID(genGID());
                cube->setColor(genIDColor());
                cube->setTypeName(true);
                element_list->append(cube);
                only_prymitive->append(element_list->size()-1);
                break;
    }
    case MEV_PRIM_PYRAMID:
    {
        Pyramid *pyramid = new Pyramid(1.0f);
        pyramid->setGID(genGID());
        pyramid->setColor(genIDColor());
        pyramid->setTypeName(true);
        element_list->append(pyramid);
        only_prymitive->append(element_list->size()-1);
        break;
    }
    case MEV_PRIM_CYLINDER:
    {
        //Pyramid *pyramid = new Pyramid(1.0f);
        //pyramid->setID(genPrimID());
        //primitives_list->append(pyramid);
        break;
    }

    }
}

void Work::addAction(int i, double obj[3])
{
    switch(i)
    {
    case MEV_GROUP:
        break;
    case MEV_TRANSLATE:
    {
        Translate *translate = new Translate(obj[0], obj[1], obj[2]);
        translate->setGID(genGID());
        element_list->append(translate);
        break;
    }
    case MEV_ROTATE:
        break;
    case MEV_SUBSTRACT:
        break;
    case MEV_INTERSECT:
        break;
    }
}

long Work::genGID()
{
    return current_free_id++;
}

int* Work::genIDColor()
{
    if(this->current_free_color[2]<255)
        current_free_color[2]++;
    else if(this->current_free_color[1]<255)
        current_free_color[1]++;
    else if(this->current_free_color[0]<255)
        current_free_color[0]++;

    return this->current_free_color;
}

QList<Element*>* Work::getList()
{
    return element_list;
}

QList<int> *Work::getOnlyPrimitiveList()
{
    return only_prymitive;
}

