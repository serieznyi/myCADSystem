#include "IntersectPrimitive.h"

IntersectPrimitive::IntersectPrimitive(Container *con1, Container *con2):GroupPrimitive(con1, con2)
{
    this->setTypeName(MEL_INTERSECT);
    container1 = con1;
    container2 = con2;
}

void IntersectPrimitive::draw()
{
    glEnable(GL_STENCIL_TEST);                          // буфер трафарета
    glStencilFunc(GL_NEVER, 1, 1);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_REPLACE);
        container1->draw(getPaintMode());
    glStencilFunc(GL_NEVER, 1, 1);
    glStencilOp(GL_INCR, GL_KEEP, GL_REPLACE);
        container2->draw(getPaintMode());

    glStencilFunc(GL_EQUAL, 2, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        container1->draw(getPaintMode());
    glStencilFunc(GL_EQUAL, 2, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
       container2->draw(getPaintMode());
    glDisable(GL_STENCIL_TEST);                          // буфер трафарета
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
