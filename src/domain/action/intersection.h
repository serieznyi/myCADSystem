//  Действие "Пересечение"

#ifndef MYCADSYSTEM_SRC_DOMAIN_ACTION_INTERSECTION_H_
#define MYCADSYSTEM_SRC_DOMAIN_ACTION_INTERSECTION_H_

#include "src/domain/action.h"

class Intersection : public Action {
 public:
  explicit Intersection();
  virtual void Apply(bool mode = true);
};

#endif //MYCADSYSTEM_SRC_DOMAIN_ACTION_INTERSECTION_H_
