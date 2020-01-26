//   Действие "Смещение"

#ifndef MYCADSYSTEM_SRC_DOMAIN_ACTION_TRANSLATE_H_
#define MYCADSYSTEM_SRC_DOMAIN_ACTION_TRANSLATE_H_

#include "src/domain/action.h"

class Translate : public Action {
 public:
  explicit Translate(double x = 0, double y = 0, double z = 0);
  virtual void Apply(int mode = true);
  void Move(double x, double y, double z);
  void MoveTo(double x, double y, double z);

 private:
  double x_, y_, z_;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_ACTION_TRANSLATE_H_
