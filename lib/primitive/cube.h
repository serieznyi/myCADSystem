#ifndef CUBE_H
#define CUBE_H

#include "lib/primitive/primitive.h"

class Cube : public Primitive
{
public:
    explicit Cube(GLfloat a);
    virtual void Apply(bool mode=true);
    virtual void draw();
public:
    GLdouble a;
};



#endif // CUBE_H
