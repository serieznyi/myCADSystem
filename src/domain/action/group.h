//  Действие "Групировка"

#ifndef MYCADSYSTEM_SRC_DOMAIN_ACTION_GROUP_H_
#define MYCADSYSTEM_SRC_DOMAIN_ACTION_GROUP_H_

#include "src/domain/action.h"

class Group : public Action {
 public:
  explicit Group();
  virtual void Apply(bool mode = true);
};

#endif
