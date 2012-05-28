#ifndef SUBSTRACTPRIMITIVE_H
#define SUBSTRACTPRIMITIVE_H

#include "lib/primitive/groupprimitive.h"
#include "lib/container.h"
#include "resource.h"

class SubstractPrimitive : public GroupPrimitive
{
public:
    SubstractPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // SUBSTRACTPRIMITIVE_H
