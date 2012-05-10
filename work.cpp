#include "work.h"
#include "mainwindow.h"
#include "QDebug"

Work::Work(QWidget *parent)
{
    pMW                         = dynamic_cast<MainWindow*>(parent);
    element_list                = new QList<Element*>;
    only_prymitive              = new QList<int>;
    current_free_id             = 0;
    current_free_color[0]       = 0;
    current_free_color[1]       = 0;
    current_free_color[2]       = 0;
    toGroupIDs[0]=-1;
    toGroupIDs[1]=-1;
    quadric                     = gluNewQuadric();
}

void Work::drawWork(bool mode)
{
    long size = element_list->size();
    glPushMatrix();
    if(size > 0)
    {
        for(int i=size-1;i>=0;i--)
        {
            Element *elem = element_list->at(i);
            elem->Apply(mode);
            if(elem->getTypeName()==MEL_PRIMITIVE)
            {
                glPopMatrix();
                glPushMatrix();
            }
        }
    }
    glPopMatrix();
}

void Work::addPrimitive(int i)
{
    switch(i)
    {
    case MEL_SPHERE:
    {
        Sphere *sphere = new Sphere(quadric, 1.0f);
        sphere->setGID(generateGID());
        generatetIDColor(sphere->getIDColor());
        generateColor(sphere->getColor());
        element_list->append(sphere);
        only_prymitive->append(element_list->size()-1);
        break;
    }
    case MEL_CUBE:
    {
        Cube *cube = new Cube(1.0f);
        cube->setGID(generateGID());
        generatetIDColor(cube->getIDColor());
        generateColor(cube->getColor());
        element_list->append(cube);
        only_prymitive->append(element_list->size()-1);
        break;
    }
    case MEL_PYRAMID:
    {
        Pyramid *pyramid = new Pyramid(1.0f);
        pyramid->setGID(generateGID());
        generatetIDColor(pyramid->getIDColor());
        generateColor(pyramid->getColor());
        element_list->append(pyramid);
        only_prymitive->append(element_list->size()-1);
        break;
    }
    case MEL_CYLINDER:
    {

        break;
    }
    case MEL_POINT: break;
    case MEL_LINE: break;
    }
}

void Work::deletePrimitive(long index)
{
    element_list->removeAt(index);
    element_list->removeAt(index-1);
    element_list->removeAt(index-2);
    only_prymitive->removeOne(index);
    generateOnlyPrimitiveList();
}

void Work::addAction(int i)
{
    switch(i)
    {
    case MEV_GROUP:
    {
        long groupObj1 = getGroupObj1();
        long groupObj2 = getGroupObj2();

        QList<Element*> *tmp = new QList<Element*>();
        //Получение объектов для групировки и удаление их из основного списка элементов сцены
        tmp->append(element_list->at(groupObj1));
        for(int i=groupObj1+1 ;i<element_list->size();i++) // Получение всех связных элементов первого объекта
        {
            Element *elem = element_list->at(i);
            if(elem->getTypeName()==MEV_ACTION)
                tmp->append(element_list->at(i));
            else
                break;
        }
        tmp->append(element_list->at(groupObj2));
        for(int i=groupObj2+1;i<element_list->size();i++) // Получение всех связных элементов второго объекта
        {
            Element *elem = element_list->at(i);
            if(elem->getTypeName()==MEV_ACTION)
                tmp->append(element_list->at(i));
            else
                break;
        }
        for(int i=0;i<tmp->size();i++) // Удаление полученных элЕментов из главного списка
        {
            Element *elem = tmp->at(i);
            element_list->removeOne(elem);
        }

        //GroupPrimitive *grpPrimitive = new GroupPrimitive(tmp);
        //  grpPrimitive->setGID(generateGID());
        //  element_list->append(grpPrimitive);
        break;
    }
    case MEV_TRANSLATE:
    {
        Translate *translate = new Translate(0,0,0);
        translate->setGID(generateGID());
        element_list->insert(pMW->selected_prim+1,translate);
        generateOnlyPrimitiveList();
        break;
    }
    case MEV_ROTATE:
    {
        Rotate *rotate = new Rotate(0,0,0);
        rotate->setGID(generateGID());
        element_list->insert(pMW->selected_prim+1,rotate);
        generateOnlyPrimitiveList();
        break;
    }
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

void Work::generatetIDColor(int arr[])
{
    if(this->current_free_color[2]<255)
    {
        arr[2] = current_free_color[2]++;
    }
    else if(this->current_free_color[1]<255)
    {
        arr[1] = current_free_color[1]++;
    }
    else if(this->current_free_color[0]<255)
    {
        arr[0] = current_free_color[0]++;
    }
}

void Work::generateColor(int arr[])
{
    for(int i=0; i<3; i++)
    {
        arr[i]=(0 + rand()%255);
        srand(time(NULL));
    }
}

QList<Element*>* Work::getList()
{
    return element_list;
}

QList<int> *Work::getOnlyPrimitiveList()
{
    return only_prymitive;
}

void Work::generateOnlyPrimitiveList()
{
    only_prymitive->clear();
    for(int i=0; i<element_list->size();i++)
    {
        if(element_list->at(i)->getTypeName()==MEL_PRIMITIVE)
            only_prymitive->append(i);
    }
}

void Work::setGroupObj1(long i)
{
    toGroupIDs[0]=i;
}

void Work::setGroupObj2(long i)
{
    toGroupIDs[1]=i;
}

long Work::getGroupObj1()
{
    return toGroupIDs[0];
}

long Work::getGroupObj2()
{
    return toGroupIDs[1];
}
