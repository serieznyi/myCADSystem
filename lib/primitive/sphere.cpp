#include "sphere.h"

Sphere::Sphere(GLUquadric *quad, GLfloat a):Cube(a)
{
    quadric = quad;
}

void Sphere::Apply(bool mode)
{
    setPaintMode(mode);
    draw();
}

void Sphere::draw()
{
    int *color = 0;
    if(getPaintMode())
    color = getColor();
            else
    color = getIDColor();
    gluSphere(quadric, a, 20, 20);
}
