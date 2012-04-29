#ifndef PYRAMID_H
#define PYRAMID_H

#include "math.h"
#include "primitive.h"

class Pyramid : public Primitive
{
public:
    explicit Pyramid(GLfloat a);
    virtual void Apply(bool mode=true);
public:
    GLdouble a;
};

#endif // PYRAMID_H
