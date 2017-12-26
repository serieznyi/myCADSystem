#ifndef CUBE_H
#define CUBE_H

#include "src/lib/lib_primitive/primitive.h"

class Cube : public Primitive
{
public:
    explicit Cube(GLfloat a);
    virtual void Apply();

public:
    GLdouble a;
};



#endif // CUBE_H
