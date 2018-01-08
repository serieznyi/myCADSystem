//  Действие "Групировка"

#ifndef LIB_LIB_ACTION_GROUP_H
#define LIB_LIB_ACTION_GROUP_H

#include "src/lib/lib_action/action.h"

class Group : public Action
{
public:
    explicit Group();
    virtual void Apply();
};

#endif
