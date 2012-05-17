#ifndef INTERSECTPRIMITIVE_H
#define INTERSECTPRIMITIVE_H

#include "lib/primitive/primitive.h"
#include "lib/container.h"
#include "resource.h"

class IntersectPrimitive : public Primitive
{
public:
    IntersectPrimitive(Container *con1, Container *con2);
    virtual void Apply(bool mode=true);
    virtual void draw();
    void SynchData();
private:
    Container *container1;
    Container *container2;
};

#endif // INTERSECTPRIMITIVE_H
