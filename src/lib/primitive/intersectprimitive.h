#ifndef INTERSECTPRIMITIVE_H
#define INTERSECTPRIMITIVE_H

#include "src/lib/primitive/groupprimitive.h"
#include "src/lib/container.h"
#include "src/resource.h"

class IntersectPrimitive : public GroupPrimitive
{
public:
    IntersectPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // INTERSECTPRIMITIVE_H
