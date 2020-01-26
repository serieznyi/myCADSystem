#include "Scale.h"

Scale::Scale(GLdouble x, GLdouble y, GLdouble z) : Action()
{
    this->x=x;
    this->y=y;
    this->z=z;
}

void Scale::Apply(int mode)
{
    glScaled(x,y,z);
}

void Scale::ScaleX(GLdouble x)
{
        this->x+=x;
}

void Scale::ScaleY(GLdouble y)
{
    this->y+=y;
}

void Scale::ScaleZ(GLdouble z)
{
    double tz = this->z;
   if(tz+=z >0.2)
    this->z+=z;
}

void Scale::ScaleYXY(GLdouble x,GLdouble y,GLdouble z)
{
    this->x+=x;
    this->y+=y;
    this->z+=z;
}
