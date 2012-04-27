#include "translate.h"
#include <QDebug>

Translate::Translate(double x, double y, double z):Action()
{
    this->x=x;
    this->y=y;
    this->z=z;
}

void Translate::Apply(bool mode)
{
    qDebug()<<x<<" "<<y<<" "<<z;
    glTranslated(x,y,z);
}

void Translate::move(double x, double y, double z)
{
    this->x+=x;
    this->y+=y;
    this->z+=z;
}

void Translate::moveTo(double x, double y, double z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}
