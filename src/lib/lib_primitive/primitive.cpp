#include "primitive.h"

Primitive::Primitive():Element()
{

}

void Primitive::draw()
{
    this->Apply();
}

int* Primitive::getColor()
{
    return this->ID_COLOR;
}

void Primitive::setColor(int *a)
{
    this->ID_COLOR = a;
}
