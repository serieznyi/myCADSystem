#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_CUBE_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_CUBE_H_

#include "src/domain/primitive.h"

class Cube : public Primitive {
 public:
  explicit Cube(GLfloat a);
  void Draw() override;
 public:
  GLdouble a_;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_CUBE_H_
