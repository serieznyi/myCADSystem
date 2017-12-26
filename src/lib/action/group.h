//  Действие "Групировка"

#ifndef GROUP_H
#define GROUP_H

#include "src/lib/action/action.h"

class Group : public Action
{
public:
    explicit Group();
    virtual void Apply(bool mode=true);
};

#endif // GROUP_H
