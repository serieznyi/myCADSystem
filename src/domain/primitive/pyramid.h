#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_PYRAMID_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_PYRAMID_H_

#include <cmath>
#include "src/domain/primitive.h"

class Pyramid : public Primitive {
 public:
  explicit Pyramid(GLfloat a);
  void Draw() override;
 private:
  GLdouble a_;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_PYRAMID_H_
