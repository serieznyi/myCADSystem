#ifndef GROUPPRIMITIVE_H
#define GROUPPRIMITIVE_H

#include "lib/primitive/primitive.h"
#include "lib/container.h"

class GroupPrimitive : public Primitive
{
public:
    GroupPrimitive(Container *con1, Container *con2);
    virtual void Apply(bool mode=true);
    virtual void draw();
private:
    Container *container1;
    Container *container2;
};

#endif // GROUPPRIMITIVE_H
