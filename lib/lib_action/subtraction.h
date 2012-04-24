//  Действие "Вычитание"

#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "lib/lib_action/action.h"

class Subtraction : public Action
{
public:
    explicit Subtraction();
    virtual void Apply();
};

#endif // SUBTRACTION_H
