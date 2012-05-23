#include "substractprimitive.h"

SubstractPrimitive::SubstractPrimitive(Container *con1, Container *con2)
{
    this->setTypeName(MEL_SUBSTRACT);
    container1 = con1;
    container2 = con2;    
    resultContainer = container1;
}

void SubstractPrimitive::draw()
{
    glStencilFunc(GL_NEVER, 1, 1); // значение mask не используется
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

    container2->draw(getPaintMode());

    glStencilFunc(GL_EQUAL, 0, 1); // значение mask не используется
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    resultContainer->draw(getPaintMode());
}

void SubstractPrimitive::SynchData()
{
    resultContainer->getPrimitive()->setIDColor(this->getIDColor());

    if(resultContainer->getPrimitive()->getTypeName()==MEL_SUBSTRACT)
    {
        SubstractPrimitive *gp = dynamic_cast<SubstractPrimitive*>(resultContainer->getPrimitive());
        gp->SynchData();
    }    
}
