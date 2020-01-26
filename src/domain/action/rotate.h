//  Действие "Вращение"

#ifndef MYCADSYSTEM_SRC_DOMAIN_ACTION_ROTATE_H_
#define MYCADSYSTEM_SRC_DOMAIN_ACTION_ROTATE_H_

#include "src/domain/action.h"

class Rotate : public Action {
 public:
  explicit Rotate(GLdouble angle_x = 0, GLdouble angle_y = 0, GLdouble angle_z = 0);
  virtual void Apply(int mode = true);

 public:
  double angle_x_;
  double angle_y_;
  double angle_z_;
  void RotateX(GLdouble angle);
  void RotateY(GLdouble angle);
  void RotateZ(GLdouble angle);
};

#endif //MYCADSYSTEM_SRC_DOMAIN_ACTION_ROTATE_H_
