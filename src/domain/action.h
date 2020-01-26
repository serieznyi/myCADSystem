// Базовый класс действий
#ifndef MYCADSYSTEM_SRC_DOMAIN_ACTION_H_
#define MYCADSYSTEM_SRC_DOMAIN_ACTION_H_

#include "src/domain/element.h"
#include "src/constants.h"

class Action : public Element {
 public:
  explicit Action(bool mode = true);
};

#endif //MYCADSYSTEM_SRC_DOMAIN_ACTION_H_
