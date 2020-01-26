#ifndef INTERSECTPRIMITIVE_H
#define INTERSECTPRIMITIVE_H

#include "GroupPrimitive.h"
#include "src/Domain/Container.h"
#include "src/constants.h"

class IntersectPrimitive : public GroupPrimitive
{
public:
    IntersectPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // INTERSECTPRIMITIVE_H
