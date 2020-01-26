#include "scale.h"

Scale::Scale(GLdouble x, GLdouble y, GLdouble z) : Action() {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}

void Scale::Apply(int mode) {
  glScaled(x_, y_, z_);
}

void Scale::ScaleX(GLdouble x) {
  this->x_ += x;
}

void Scale::ScaleY(GLdouble y) {
  this->y_ += y;
}

void Scale::ScaleZ(GLdouble z) {
  double tz = this->z_;
  if (tz += z > 0.2)
    this->z_ += z;
}

void Scale::ScaleYxy(GLdouble x, GLdouble y, GLdouble z) {
  this->x_ += x;
  this->y_ += y;
  this->z_ += z;
}
