#ifndef SPHERE_H
#define SPHERE_H

#include "GL/glu.h"
#include "lib/primitive/primitive.h"
#include "GL/glu.h"

class Sphere : public Primitive
{
public:
    Sphere(GLUquadric *quad, GLfloat a);
    void draw();
    void setQuadric(GLUquadric quad);
private:
    GLUquadric               *quadric;
     GLdouble a;
};

#endif // SPHERE_H
