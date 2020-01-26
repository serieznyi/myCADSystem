#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_SPHERE_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_SPHERE_H_

#include "GL/glu.h"
#include "src/domain/primitive.h"
#include "GL/glu.h"

class Sphere : public Primitive {
 public:
  Sphere(GLUquadric *quad, GLfloat a);
  void Draw() override;
  void SetQuadric(GLUquadric *quad);
 private:
  GLUquadric *quadric_;
  GLdouble a_;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_SPHERE_H_
