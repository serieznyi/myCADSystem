// Базовый класс действий
#ifndef ACTION_H
#define ACTION_H

#include "src/domain/element.h"
#include "src/constants.h"

class Action : public Element {
 public:
  explicit Action(bool mode = true);
};

#endif // ACTION_H
