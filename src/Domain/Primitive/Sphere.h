#ifndef SPHERE_H
#define SPHERE_H

#include "GL/glu.h"
#include "src/Domain/Primitive.h"
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
