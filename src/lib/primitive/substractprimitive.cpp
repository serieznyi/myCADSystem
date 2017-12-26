#include "substractprimitive.h"

SubstractPrimitive::SubstractPrimitive(Container *con1, Container *con2):GroupPrimitive(con1, con2)
{
    this->setTypeName(MEL_SUBSTRACT);
    container1 = con1;
    container2 = con2;    
}

void SubstractPrimitive::draw()
{
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NEVER, 1, 1); // значение mask не используется
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

    container2->draw(getPaintMode());

    glStencilFunc(GL_EQUAL, 0, 1); // значение mask не используется
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    container1->draw(getPaintMode());
    glDisable(GL_STENCIL_TEST);
}

void SubstractPrimitive::SynchData()
{
    container1->getPrimitive()->setIDColor(this->getIDColor());

    if(container1->getPrimitive()->getTypeName()==MEL_SUBSTRACT)
    {
        SubstractPrimitive *gp = dynamic_cast<SubstractPrimitive*>(container1->getPrimitive());
        gp->SynchData();
    }    
}
