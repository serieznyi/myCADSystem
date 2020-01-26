//  Действие "Пересечение"

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "src/domain/action.h"

class Intersection : public Action
{
public:
    explicit Intersection();
    virtual void Apply(bool mode=true);
};

#endif // INTERSECTION_H
