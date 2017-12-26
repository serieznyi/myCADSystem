//  Действие "Пересечение"

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "lib/lib_action/action.h"

class Intersection : public Action
{
public:
    explicit Intersection();
    virtual void Apply();
};

#endif // INTERSECTION_H
