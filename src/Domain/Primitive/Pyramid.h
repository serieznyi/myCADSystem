#ifndef PYRAMID_H
#define PYRAMID_H

#include "math.h"
#include "src/Domain/Primitive.h"

class Pyramid : public Primitive
{
public:
    explicit Pyramid(GLfloat a);
    virtual void draw();
private:
    GLdouble a;
};

#endif // PYRAMID_H
