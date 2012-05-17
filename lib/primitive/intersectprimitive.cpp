#include "intersectprimitive.h"

IntersectPrimitive::IntersectPrimitive(Container *con1, Container *con2)
{
    this->setTypeName(MEL_GROUP);
    container1 = con1;
    container2 = con2;
}


void IntersectPrimitive::Apply(bool mode)
{
    setPaintMode(mode);
    draw();
}

void IntersectPrimitive::draw()
{
    glStencilFunc(GL_NEVER, 1, 1);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        container1->draw(getPaintMode());
    glStencilFunc(GL_NEVER, 1, 1);
    glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);
        container1->draw(getPaintMode());

    glStencilFunc(GL_EQUAL, 2, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        container1->draw(getPaintMode());
    glStencilFunc(GL_EQUAL, 2, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
       container1->draw(getPaintMode());


}

void IntersectPrimitive::SynchData()
{
    container1->getPrimitive()->setIDColor(this->getIDColor());
    container1->getPrimitive()->setColor(this->getColor());

    container2->getPrimitive()->setIDColor(this->getIDColor());
    container2->getPrimitive()->setColor(this->getColor());

    if(container1->getPrimitive()->getTypeName()==MEL_INTERSECT)
    {
        IntersectPrimitive *gp = dynamic_cast<IntersectPrimitive*>(container1->getPrimitive());
        gp->SynchData();

    }
    if(container2->getPrimitive()->getTypeName()==MEL_INTERSECT)
    {
        IntersectPrimitive *gp = dynamic_cast<IntersectPrimitive*>(container2->getPrimitive());
        gp->SynchData();
    }
}
