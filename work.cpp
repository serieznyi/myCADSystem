#include "work.h"
#include "QDebug"

Work::Work()
{
    element_list                = new QList<Element*>;
    only_prymitive              = new QList<int>;
    current_free_id             = 0;
    current_free_color[0]       = 0;
    current_free_color[1]       = 0;
    current_free_color[2]       = -1;
}

void Work::drawWork(bool mode)
{
    long size = element_list->size();
    glPushMatrix();
    if(size > 0)
    {
        for(int i=0;i<size;i++)
        {
            Element *elem = element_list->at(i);
            elem->Apply(mode);
            if(elem->getTypeName()==MEL_PRIMITIVE)
            {
                glPopMatrix();
                glPushMatrix();
            }
        }
       glPopMatrix();
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
        Translate *translate = new Translate(1, 0, 1);
        translate->setGID(generateGID());
        element_list->append(translate);
            Rotate *rotate = new Rotate(0,0,0);
            rotate->setGID(generateGID());
            element_list->append(rotate);
                Cube *cube = new Cube(1.0f);
                cube->setGID(generateGID());
                cube->setIDColor(generatetIDColor());
                cube->setColor(generateColor());
                element_list->append(cube);
                only_prymitive->append(element_list->size()-1);
                break;
    }
    case MEV_PRIM_PYRAMID:
    {
        Translate *translate = new Translate(0, 0, 0);
        translate->setGID(generateGID());
        element_list->append(translate);
            Rotate *rotate = new Rotate(0,0,0);
            rotate->setGID(generateGID());
            element_list->append(rotate);
                Pyramid *pyramid = new Pyramid(1.0f);
                pyramid->setGID(generateGID());
                pyramid->setIDColor(generatetIDColor());
                pyramid->setColor(generateColor());
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
        translate->setGID(generateGID());
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

long Work::generateGID()
{
    return current_free_id++;
}

int* Work::generatetIDColor()
{
    if(this->current_free_color[2]<255)
        current_free_color[2]++;
    else if(this->current_free_color[1]<255)
        current_free_color[1]++;
    else if(this->current_free_color[0]<255)
        current_free_color[0]++;
    //qDebug()<<"ID COLOR"<<current_free_color[0]<<" "<<current_free_color[1]<<" "<<current_free_color[2];

    return this->current_free_color;
}

int* Work::generateColor()
{
    for(int i=0; i<3; i++)
    {
        this->real_color[i]=(0 + rand()%255);
        srand(time(NULL));
    }
    //qDebug()<<"REAL COLOR"<<real_color[0]<<" "<<real_color[1]<<" "<<real_color[2];
    return this->real_color;
}

QList<Element*>* Work::getList()
{
    return element_list;
}

QList<int> *Work::getOnlyPrimitiveList()
{
    return only_prymitive;
}

