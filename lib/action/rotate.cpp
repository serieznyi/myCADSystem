#include "rotate.h"

Rotate::Rotate(double angleX, double angleY, double angleZ):Action()
{
    this->angleX=angleX;
    this->angleY=angleY;
    this->angleZ=angleZ;
}

void Rotate::Apply(bool mode)
{
    glRotated(angleX, 1, 0, 0);
    glRotated(angleY, 0, 1, 0);
    glRotated(angleZ, 0, 0, 1);
}

void Rotate::RotateX(GLdouble angle)
{
    this->angleX+=angle;
}

void Rotate::RotateY(GLdouble angle)
{
    this->angleY+=angle;
}

void Rotate::RotateZ(GLdouble angle)
{
    this->angleZ+=angle;
}



