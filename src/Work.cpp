#include <src/Domain/Primitive/Sphere.h>
#include <src/Domain/Primitive/Cube.h>
#include <src/Domain/Primitive/Pyramid.h>
#include <src/Domain/Primitive/GroupPrimitive.h>
#include <src/Domain/Primitive/SubstractPrimitive.h>
#include <src/Domain/Primitive/IntersectPrimitive.h>
#include "Work.h"
#include "src/gui/MainWindow.h"
#include "QDebug"

Work::Work(QWidget *parent)
{
    pMW                         = dynamic_cast<MainWindow*>(parent);
    element_list                = new QList<Container*>;
    current_free_id             = 0;
    current_free_color[0]       = 0;
    current_free_color[1]       = 0;
    current_free_color[2]       = 0;
    forGroupID[0]=-1;
    forGroupID[1]=-1;

    quadric                     = gluNewQuadric();
}

void Work::drawWork(bool mode)
{
    glPushMatrix();

    for(int i=0;i<element_list->size();i++){
        Container *cont = element_list->at(i);
        cont->draw(mode);
        switch(cont->getPrimitive()->getTypeName())
        {
        case MEL_PRIMITIVE:
        case MEL_CUBE:
        case MEL_PYRAMID:
        case MEL_SPHERE:
        case MEL_GROUP:
        case MEL_CYLINDER:
            glPopMatrix();
            glPushMatrix();
        default:break;
        }
    }
    glPopMatrix();
}

void Work::addPrimitive(int i, QPoint pos)
{
    switch(i)
    {
    case MEL_SPHERE:
    {
        Sphere *sphere = new Sphere(quadric, 1.0f);
        sphere->setGID(generateGID());
        sphere->setIDColor(generateIDColor());
        sphere->setColor(generateColor());
        element_list->append(new Container(sphere));
        break;
    }
    case MEL_CUBE:
    {
        Cube *cube = new Cube(1.0f);
        cube->setGID(generateGID());
        cube->setIDColor(generateIDColor());
        cube->setColor(generateColor());
        if(pos.x()!=0&&pos.y()!=0)
            element_list->append(new Container(cube, new Translate(pos.x(), pos.y(), 0)));
        else
            element_list->append(new Container(cube));
        break;
    }
    case MEL_PYRAMID:
    {
        Pyramid *pyramid = new Pyramid(2.0f);
        pyramid->setGID(generateGID());
        pyramid->setIDColor(generateIDColor());
        pyramid->setColor(generateColor());
        element_list->append(new Container(pyramid));
        break;
    }
    case MEL_CYLINDER:
    {

        break;
    }
    }
}

void Work::deletePrimitive(long index)
{
    element_list->removeAt(index);
}

void Work::addAction(int i)
{
    switch(i)
    {
    case ACTION_GROUP:
    {
        Container *obj1 = element_list->at(getGroupObj1());
        Container *obj2 = element_list->at(getGroupObj2());

        GroupPrimitive *groupPrim = new GroupPrimitive(obj1, obj2);
        groupPrim->setGID(generateGID());
        groupPrim->setIDColor(generateIDColor());
        groupPrim->setColor(generateColor());
        groupPrim->SynchData();
        element_list->removeOne(obj1);
        element_list->removeOne(obj2);
        element_list->append(new Container(groupPrim));
        break;
    }
    case ACTION_SUBSTRACT:
    {
        Container *obj1 = element_list->at(getGroupObj1());
        Container *obj2 = element_list->at(getGroupObj2());

        SubstractPrimitive *substractPrim = new SubstractPrimitive(obj1, obj2);
        substractPrim->setGID(generateGID());
        substractPrim->setIDColor(generateIDColor());
        substractPrim->setColor(generateColor());
        substractPrim->SynchData();
        element_list->removeOne(obj1);
        element_list->removeOne(obj2);
        element_list->append(new Container(substractPrim));
        break;
    }
    case ACTION_TRANSLATE:
    {
        Translate *translate = new Translate(0,0,0);
        translate->setGID(generateGID());
        element_list->at(pMW->selected_prim)->addTranslate(translate);
        break;
    }
    case ACTION_SCALE:
    case ACTION_STRETCH:
    {
        Scale *scale = new Scale(1,1,1);
        scale->setGID(generateGID());
        element_list->at(pMW->selected_prim)->addScale(scale);
        break;
    }

    case ACTION_ROTATE:
    {
        Rotate *rotate = new Rotate(0,0,0);
        rotate->setGID(generateGID());
        element_list->at(pMW->selected_prim)->addRotate(rotate);
        break;
    }
    case ACTION_INTERSECT:
    {
        Container *obj1 = element_list->at(getGroupObj1());
        Container *obj2 = element_list->at(getGroupObj2());

        IntersectPrimitive *intersectPrim = new IntersectPrimitive(obj1, obj2);
        intersectPrim->setGID(generateGID());
        intersectPrim->setIDColor(generateIDColor());
        intersectPrim->setColor(generateColor());
        intersectPrim->SynchData();
        element_list->removeOne(obj1);
        element_list->removeOne(obj2);
        element_list->append(new Container(intersectPrim));
        break;
    }
    default:
        break;
    }
}

long Work::generateGID()
{
    return current_free_id++;
}

MCOLOR* Work::generateIDColor()
{
    int arr[3]={0};

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
    MCOLOR *color;
    color = new MCOLOR(arr[0],arr[1],arr[2]);
    return color;
}

MCOLOR* Work::generateColor()
{
    int arr[3]={0};
    MCOLOR *color;
    for(int i=0; i<3; i++)
    {
        arr[i]=(0 + rand()%255);
        srand(time(NULL));
    }
    color = new MCOLOR(arr[0],arr[1],arr[2]);
    return color;
}

QList<Container*>* Work::getList()
{
    return element_list;
}

void Work::setGroupObj1(long i)
{
    forGroupID[0]=i;
}

void Work::setGroupObj2(long i)
{
    forGroupID[1]=i;
}

long Work::getGroupObj1()
{
    return forGroupID[0];
}

long Work::getGroupObj2()
{
    return forGroupID[1];
}
