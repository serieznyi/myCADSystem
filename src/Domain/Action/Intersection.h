//  Действие "Пересечение"

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "src/Domain/Action.h"

class Intersection : public Action
{
public:
    explicit Intersection();
    virtual void Apply(bool mode=true);
};

#endif // INTERSECTION_H
