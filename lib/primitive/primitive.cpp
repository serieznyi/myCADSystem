#include "primitive.h"

Primitive::Primitive():Element()
{
    idcolors_arr = new QStack<MCOLOR*>();
    this->setTypeName(MEL_PRIMITIVE);
}

void Primitive::setIDColor(MCOLOR *color)
{
    idcolors_arr->push(color);
    ID_COLOR = color;
}

void Primitive::setColor(MCOLOR *color)
{
    this->COLOR = color;
}

MCOLOR* Primitive::getIDColor()
{
    return this->COLOR;
}

MCOLOR* Primitive::getColor()
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
