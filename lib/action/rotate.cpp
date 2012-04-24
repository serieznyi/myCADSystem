#include "rotate.h"

Rotate::Rotate(double angleX, double angleY, double angleZ):Action()
{
    this->angleX=angleX;
    this->angleY=angleY;
    this->angleZ=angleZ;
}

void Rotate::Apply()
{
    glRotated(angleX, 1, 0, 0);
    glRotated(angleY, 0, 1, 0);
    glRotated(angleZ, 0, 0, 1);
}

void Rotate::RotateX(double angle)
{
    this->angleX+=angle;
}

void Rotate::RotateY(double angle)
{
    this->angleY+=angle;
}

void Rotate::RotateZ(double angle)
{
    this->angleZ+=angle;
}



