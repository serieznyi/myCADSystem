#ifndef GROUP_PRIMITIVE_H
#define GROUP_PRIMITIVE_H

#include "lib/primitive/primitive.h"

class GroupPrimitive : public Primitive
{
public:
    explicit GroupPrimitive(QList<Element *> *element);
};

#endif // GROUP_PRIMITIVE_H
