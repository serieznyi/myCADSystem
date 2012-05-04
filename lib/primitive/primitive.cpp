#include "primitive.h"

Primitive::Primitive():Element()
{
    //memset(ID_COLOR, 0, 3);
    //memset(COLOR, 0, 3);
    ID_COLOR[0]=ID_COLOR[1]=ID_COLOR[2]=0;
    COLOR[0]=COLOR[1]=COLOR[2]=0;
    this->setTypeName(MEL_PRIMITIVE);
}

int* Primitive::getIDColor()
{
    return this->ID_COLOR;
}

int* Primitive::getColor()
{
    return this->COLOR;
}

void Primitive::setPaintMode(int mode)
{
    this->PAINT_MODE = mode;
}

int Primitive::getPaintMode()
{
    return PAINT_MODE;
}

void Primitive::draw()
{


}
