#ifndef SUBSTRACTPRIMITIVE_H
#define SUBSTRACTPRIMITIVE_H

#include "src/lib/primitive/GroupPrimitive.h"
#include "src/lib/Container.h"
#include "src/resource.h"

class SubstractPrimitive : public GroupPrimitive
{
public:
    SubstractPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // SUBSTRACTPRIMITIVE_H
