#include "sphere.h"

Sphere::Sphere(GLUquadric *quad, GLfloat a):Primitive()
{
    this->a = a;
    this->setTypeName(MEL_SPHERE);
    quadric = quad;
}

void Sphere::draw()
{
    MCOLOR *color = 0;
    if(getPaintMode())
    color = getColor();
            else
    color = getIDColor();

    glColor3ub(color->red,color->green,color->blue);

    gluSphere(quadric, a, 20, 20);
}
