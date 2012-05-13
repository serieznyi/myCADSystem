#include "groupprimitive.h"

GroupPrimitive::GroupPrimitive(Container *con1, Container *con2)
{
    container1 = con1;
    container2 = con2;
}

void GroupPrimitive::Apply(bool mode)
{
    setPaintMode(mode);
    draw();
}

void GroupPrimitive::draw()
{
    container1->draw(getPaintMode());
    container2->draw(getPaintMode());
}

void GroupPrimitive::SynchData()
{
    container1->getPrimitive()->setIDColor(this->getIDColor());
    container1->getPrimitive()->setColor(this->getColor());

    container2->getPrimitive()->setIDColor(this->getIDColor());
    container2->getPrimitive()->setColor(this->getColor());
}
