#include "primitive.h"

Primitive::Primitive():Element()
{

}

void Primitive::draw()
{
    // TODO remove not required argument in virtual method
    this->Apply(0);
}

int* Primitive::getColor()
{
    return this->ID_COLOR;
}

void Primitive::setColor(int *a)
{
    this->ID_COLOR = a;
}
