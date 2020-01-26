#include "group-primitive.h"

GroupPrimitive::GroupPrimitive(Container *con1, Container *con2):Primitive()
{
    this->setTypeName(MEL_GROUP);
    container1 = con1;
    container2 = con2;
}

void GroupPrimitive::draw()
{
    container1->draw(getPaintMode());
    container2->draw(getPaintMode());
}

void GroupPrimitive::SynchData()
{
    container1->getPrimitive()->setIDColor(this->getIDColor());
 //   container1->getPrimitive()->setColor(this->getColor());

    container2->getPrimitive()->setIDColor(this->getIDColor());
  //  container2->getPrimitive()->setColor(this->getColor());

    if(container1->getPrimitive()->getTypeName()==MEL_GROUP)
    {
        GroupPrimitive *gp = dynamic_cast<GroupPrimitive*>(container1->getPrimitive());
        gp->SynchData();

    }
    if(container2->getPrimitive()->getTypeName()==MEL_GROUP)
    {
        GroupPrimitive *gp = dynamic_cast<GroupPrimitive*>(container2->getPrimitive());
        gp->SynchData();
    }
}
