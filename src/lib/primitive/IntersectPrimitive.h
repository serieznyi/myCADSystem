#ifndef INTERSECTPRIMITIVE_H
#define INTERSECTPRIMITIVE_H

#include "src/lib/primitive/GroupPrimitive.h"
#include "src/lib/Container.h"
#include "src/resource.h"

class IntersectPrimitive : public GroupPrimitive
{
public:
    IntersectPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // INTERSECTPRIMITIVE_H
