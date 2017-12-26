//  Действие "Групировка"

#ifndef GROUP_H
#define GROUP_H

#include "src/lib/lib_action/action.h"

class Group : public Action
{
public:
    explicit Group();
    virtual void Apply();
};

#endif // GROUP_H
