//  Действие "Групировка"

#ifndef LIB_ACTION_GROUP_H
#define LIB_ACTION_GROUP_H

#include "src/domain/action.h"

class Group : public Action {
 public:
  explicit Group();
  virtual void Apply(bool mode = true);
};

#endif
