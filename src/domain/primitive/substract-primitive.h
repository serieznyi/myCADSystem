#ifndef SUBSTRACTPRIMITIVE_H
#define SUBSTRACTPRIMITIVE_H

#include "group-primitive.h"
#include "src/domain/container.h"
#include "src/constants.h"

class SubstractPrimitive : public GroupPrimitive
{
public:
    SubstractPrimitive(Container *con1, Container *con2);
    virtual void draw();
    virtual void SynchData();
};

#endif // SUBSTRACTPRIMITIVE_H
