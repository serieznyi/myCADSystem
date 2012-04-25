#ifndef PYRAMID_H
#define PYRAMID_H

#include "math.h"
#include "cube.h"

class Pyramid : public Cube
{
public:
    explicit Pyramid(GLfloat a);
    virtual void Apply(bool mode=true);
};

#endif // PYRAMID_H
