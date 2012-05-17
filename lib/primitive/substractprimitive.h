#ifndef SUBSTRACTPRIMITIVE_H
#define SUBSTRACTPRIMITIVE_H

#include "lib/primitive/primitive.h"
#include "lib/container.h"
#include "resource.h"

class SubstractPrimitive : public Primitive
{
public:
    SubstractPrimitive(Container *con1, Container *con2);
    virtual void Apply(bool mode=true);
    virtual void draw();
    void SynchData();
private:
    Container *container1;
    Container *container2;
    Container *resultContainer;
};

#endif // SUBSTRACTPRIMITIVE_H
