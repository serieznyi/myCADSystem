#ifndef GROUP_PRIMITIVE_H
#define GROUP_PRIMITIVE_H

#include "lib/lib.h"

class Group_primitive : public Primitive
{
public:
    Group_primitive(long obj1, long obj2);
    void addObj1(Translate *tr, Rotate *rot, Primitive prim);
    void addObj2(Translate *tr, Rotate *rot, Primitive prim);
public:
    Translate *trans1, trans2;
    Rotate  *rot1, rot2;
    Primitive *prim1, prim2;
};

#endif // GROUP_PRIMITIVE_H
