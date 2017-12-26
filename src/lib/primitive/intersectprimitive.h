#ifndef INTERSECTPRIMITIVE_H
#define INTERSECTPRIMITIVE_H

#include "lib/primitive/groupprimitive.h"
#include "lib/container.h"
#include "resource.h"

class IntersectPrimitive : public GroupPrimitive
{
public:
    IntersectPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // INTERSECTPRIMITIVE_H
