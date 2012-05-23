#ifndef SPHERE_H
#define SPHERE_H

#include "GL/glu.h"
#include "lib/primitive/cube.h"
#include "GL/glu.h"

class Sphere : public Cube
{
public:
    Sphere(GLUquadric *quad, GLfloat a);
    void draw();
    void setQuadric(GLUquadric quad);
private:
    GLUquadric               *quadric;
};

#endif // SPHERE_H
