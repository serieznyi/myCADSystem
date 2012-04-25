#include "primitive.h"

Primitive::Primitive():Element()
{
    this->setTypeName(MEL_PRIMITIVE);
}

int* Primitive::getIDColor()
{
    return this->ID_COLOR;
}

void Primitive::setIDColor(int *a)
{
    this->ID_COLOR = a;
}

int* Primitive::getColor()
{
    return this->COLOR;
}

void Primitive::setColor(int *a)
{
    this->COLOR = a;
}
