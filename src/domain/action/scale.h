#ifndef MYCADSYSTEM_SRC_DOMAIN_ACTION_SCALE_H_
#define MYCADSYSTEM_SRC_DOMAIN_ACTION_SCALE_H_

#include "src/domain/action.h"

class Scale : public Action {
 public:
  Scale(GLdouble x, GLdouble y, GLdouble z);
  virtual void Apply(int mode);
  void ScaleX(GLdouble x);
  void ScaleY(GLdouble y);
  void ScaleZ(GLdouble z);
  void ScaleYxy(GLdouble x, GLdouble y, GLdouble z);
 private:
  double x_, y_, z_;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_ACTION_SCALE_H_
