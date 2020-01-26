//  Действие "Групировка"

#ifndef LIB_ACTION_GROUP_H
#define LIB_ACTION_GROUP_H

#include "src/Domain/Action.h"

class Group : public Action
{
public:
    explicit Group();
    virtual void Apply(bool mode=true);
};

#endif
